#pragma once

#include <string>
#include <array>
#include <cstdint>

extern "C" {
#include <secp256k1.h>
#include <secp256k1_recovery.h>
}

#include <ethash/keccak.hpp>
#include "FixedHash.h"

namespace dev
{

class Signer
{
public:
    static Signer& getInstance()
    {
        static Signer instance;
        return instance;
    }

    bool setPrivateKey(const std::string& hexKey)
    {
        std::string key = hexKey;
        if (key.length() >= 2 && key.substr(0, 2) == "0x")
            key = key.substr(2);
        
        if (key.length() != 64)
            return false;

        for (size_t i = 0; i < 32; i++)
        {
            m_privateKey[i] = static_cast<uint8_t>(std::stoi(key.substr(i * 2, 2), nullptr, 16));
        }
        
        m_hasKey = true; std::cerr << "Private key loaded, first byte: " << (int)m_privateKey[0] << std::endl;
        computeAddress();
        return true;
    }

    std::array<uint8_t, 65> sign(const h256& hash)
    {
        std::array<uint8_t, 65> signature = {};
        
        if (!m_hasKey)
            return signature;

        secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
        secp256k1_ecdsa_recoverable_signature sig;

        if (secp256k1_ecdsa_sign_recoverable(ctx, &sig, hash.data(), m_privateKey.data(), nullptr, nullptr))
        {
            int recid;
            secp256k1_ecdsa_recoverable_signature_serialize_compact(ctx, signature.data(), &recid, &sig);
            signature[64] = static_cast<uint8_t>(recid + 27);
        }

        secp256k1_context_destroy(ctx);
        return signature;
    }

    std::array<uint8_t, 65> signBlockNumber(int blockNum)
    {
        // Create hash from block number (same as Go: binary.BigEndian + Keccak256)
        uint8_t blockNumBytes[8] = {0};
        uint64_t bn = static_cast<uint64_t>(blockNum);
        blockNumBytes[0] = (bn >> 56) & 0xFF;
        blockNumBytes[1] = (bn >> 48) & 0xFF;
        blockNumBytes[2] = (bn >> 40) & 0xFF;
        blockNumBytes[3] = (bn >> 32) & 0xFF;
        blockNumBytes[4] = (bn >> 24) & 0xFF;
        blockNumBytes[5] = (bn >> 16) & 0xFF;
        blockNumBytes[6] = (bn >> 8) & 0xFF;
        blockNumBytes[7] = bn & 0xFF;
        
        auto hash = ethash::keccak256(blockNumBytes, 8);
        h256 messageHash;
        memcpy(messageHash.data(), hash.bytes, 32);
        auto sig = sign(messageHash); std::cerr << "signBlockNumber: block=" << blockNum << " sig[0]=" << (int)sig[0] << " sig[64]=" << (int)sig[64] << std::endl; return sig;
    }

    bool hasKey() const { return m_hasKey; }
    
    const h160& getAddress() const { return m_address; }
    
    std::string getAddressHex() const 
    { 
        return "0x" + m_address.hex(); 
    }

private:
    Signer() : m_hasKey(false) {}
    
    void computeAddress()
    {
        secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
        secp256k1_pubkey pubkey;
        
        if (secp256k1_ec_pubkey_create(ctx, &pubkey, m_privateKey.data()))
        {
            uint8_t pubkeySerialized[65];
            size_t pubkeyLen = 65;
            secp256k1_ec_pubkey_serialize(ctx, pubkeySerialized, &pubkeyLen, &pubkey, SECP256K1_EC_UNCOMPRESSED);
            
            // Keccak256 of public key (skip first byte 0x04)
            auto hash = ethash::keccak256(pubkeySerialized + 1, 64);
            
            // Take last 20 bytes
            memcpy(m_address.data(), hash.bytes + 12, 20);
        }
        
        secp256k1_context_destroy(ctx);
    }

    std::array<uint8_t, 32> m_privateKey;
    h160 m_address;
    bool m_hasKey;
};

}  // namespace dev
