// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0x55;
        pchMessageStart[2] = 0x1a;
        pchMessageStart[3] = 0xd7;
        vAlertPubKey = ParseHex("09f66784d27a9745bc6b132c04b94baafbba5d5257fe028e74682a62f7c2f81f85d113a216df3be197653f454852a2d08c6314aad5ca3cbe9977428ca9e1e1feef");
        nDefaultPort = 9101;
        nRPCPort = 9102;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "Google’s DeepMind Scrutinized Over Accessing NHS Patient Records - JP Buntinx - May 18, 2017"; 
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1495135800, vin, vout, 0); 
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1495135800; 
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 198446;

        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == a82e164d530c828b63ca1ba4cea37613f472f70e2bb43e4ff75ccb8f0267be77
        block.nTime = 1495135800
        block.nNonce = 198446
        block.GetHash = 000001dfdbeabbed2b354ef100193ec4e235f095993b9236f1d910c5ae88c97a
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001dfdbeabbed2b354ef100193ec4e235f095993b9236f1d910c5ae88c97a"));
        assert(genesis.hashMerkleRoot == uint256("0xa82e164d530c828b63ca1ba4cea37613f472f70e2bb43e4ff75ccb8f0267be77"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,99);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,104);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        //vSeeds.push_back(CDNSSeedData("Seed01",  "91.134.120.210"));

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 2 * 60; // Initially ~2 Min during PoW
        if(nBestHeight > nStartPoSBlock) // Scaled up for PoW/PoS twin phase
        {
            nTargetSpacing = 6 * 60;
        }
        nTargetTimespan = 2 * nTargetSpacing;
        nLastPoWBlock = 100000; // PoW ends on block 100k
        nStartPoSBlock = 250;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0x58;
        pchMessageStart[2] = 0x1b;
        pchMessageStart[3] = 0xd9;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 22);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 18);

        vAlertPubKey = ParseHex("09f66784d27a9745bc6b132c04b94baafbba5d5257fe028e74682a62f7c2f81f85d113a216df3be197653f454852a2d08c6314aad5ca3cbe9977428ca9e1e1faaf");
        nDefaultPort = 9104;
        nRPCPort = 9105;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime    = 1495135800+60; 
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2472997;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == a82e164d530c828b63ca1ba4cea37613f472f70e2bb43e4ff75ccb8f0267be77
        block.nTime = 1495135860
        block.nNonce = 2472997
        block.GetHash = 000002625862303fdd95c4564b17208f8960fbe048dcb39fd122d73001dbb10c
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000002625862303fdd95c4564b17208f8960fbe048dcb39fd122d73001dbb10c"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,64);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,11);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,103);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 2 * 60;
        nLastPoWBlock = 0x7fffffff;
        nStartPoSBlock = 5;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xe1;
        pchMessageStart[1] = 0x75;
        pchMessageStart[2] = 0x2a;
        pchMessageStart[3] = 0xe7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1495135800+90;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 9103;
        strDataDir = "regtest";

        /** Genesis Block RegNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == a82e164d530c828b63ca1ba4cea37613f472f70e2bb43e4ff75ccb8f0267be77
        block.nTime = 1495135890
        block.nNonce = 8
        block.GetHash = ae4b40e41669e7c497154c361e0aa3687fdfc9999ae410f35429ff75bcfd4ec6
        */

        assert(hashGenesisBlock == uint256("0xae4b40e41669e7c497154c361e0aa3687fdfc9999ae410f35429ff75bcfd4ec6"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
