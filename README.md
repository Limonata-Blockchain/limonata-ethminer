# 🍋 Limonata Ethminer

Modified ethminer with block signing support for Limonata's NFT-gated mining system.

> ⚠️ **Standard miners (lolMiner, T-Rex, etc.) will NOT work with Limonata.** You must use this modified ethminer.

---

## 🚀 Features

- ✅ Block signature support for NFT-gated mining
- ✅ Delegate mining key support (keep your main wallet secure)
- ✅ Compatible with Limonata's modified DAG
- ✅ OpenCL and CUDA support

---

## 📥 Download

### Pre-built Binaries

| Platform | Download |
|----------|----------|
| Linux (Ubuntu 20.04+) | [ethminer-limonata-linux.tar.gz](https://github.com/Limonata-Blockchain/limonata-ethminer/releases) |
| Windows | Coming soon |

### Build from Source
```bash
git clone https://github.com/Limonata-Blockchain/limonata-ethminer.git
cd limonata-ethminer
git submodule update --init --recursive
mkdir build && cd build
cmake .. -DETHASHCL=ON -DETHASHCUDA=ON
cmake --build . --config Release
```

### Dependencies (Ubuntu)
```bash
sudo apt-get install -y \
  build-essential \
  cmake \
  git \
  libboost-all-dev \
  mesa-common-dev \
  ocl-icd-opencl-dev
```

---

## 🔧 Usage

### Basic Mining (Direct Key)
```bash
./ethminer \
  --miner-privatekey YOUR_PRIVATE_KEY \
  -G \
  -P stratum1+tcp://YOUR_WALLET.rig1@pool.limonata.xyz:3333
```

### Secure Mining with Delegate Key (Recommended)

1. Setup your delegate key at **pool.limonata.xyz/setup.html**
2. Register the delegate on blockchain with MetaMask
3. Mine with the delegate key:
```bash
./ethminer \
  --miner-privatekey YOUR_DELEGATE_PRIVATE_KEY \
  -G \
  -P stratum1+tcp://YOUR_NFT_WALLET.rig1@pool.limonata.xyz:3333
```

### Options

| Option | Description |
|--------|-------------|
| `--miner-privatekey <key>` | Private key for signing blocks (required) |
| `-G` | Use OpenCL (AMD/NVIDIA) |
| `-U` | Use CUDA (NVIDIA only) |
| `-P <url>` | Pool connection URL |

---

## 🛡️ Security: Why Use a Delegate Key?

Your miner needs a private key to sign blocks. Using a delegate key keeps your main wallet secure:

| Benefit | Description |
|---------|-------------|
| 🛡️ Main Wallet Protected | Your NFT and funds never leave your secure wallet |
| 🔒 If Key Compromised | Attacker can only mine FOR you - rewards still go to your wallet |
| ⚡ Easy to Revoke | One click to revoke and create a new mining key anytime |

---

## 📋 Requirements

- **Mining License NFT** - Get one at [limonata.xyz](https://limonata.xyz)
- **GPU with 4GB+ VRAM** - DAG is capped at 4GB
- **Linux (Ubuntu 20.04+)** or Windows (coming soon)

---

## 🔗 Links

| Resource | URL |
|----------|-----|
| 🌐 Website | [limonata.xyz](https://limonata.xyz) |
| ⛏️ Mining Pool | [pool.limonata.xyz](https://pool.limonata.xyz) |
| 🔍 Explorer | [explorer.limonata.xyz](https://explorer.limonata.xyz) |
| 📖 Setup Guide | [pool.limonata.xyz/setup.html](https://pool.limonata.xyz/setup.html) |

---

## ⚖️ License

GNU General Public License v3.0

Based on [ethereum-mining/ethminer](https://github.com/ethereum-mining/ethminer)

---

<p align="center">
  <b>🍋 Limonata - Fresh Blocks, Squeezed Daily 🍋</b>
</p>
