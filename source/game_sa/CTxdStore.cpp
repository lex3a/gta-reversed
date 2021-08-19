/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"
#include "CTxdStore.h"

CPool<TxdDef>*& CTxdStore::ms_pTxdPool = *reinterpret_cast<CPool<TxdDef>**>(0xC8800C);
RwTexDictionary*& CTxdStore::ms_pStoredTxd = *reinterpret_cast<RwTexDictionary**>(0xC88010);
int32_t& CTxdStore::ms_lastSlotFound = *reinterpret_cast<int32_t*>(0xC88014);

int16_t (&CTxdStore::defaultTxds)[4] = *reinterpret_cast<int16_t (*)[4]>(0xC88004);

int32_t& TexDictionaryLinkPluginOffset = *reinterpret_cast<int32_t*>(0xC88018);

// variables list is not finished. Need to make CPools before.

void CTxdStore::InjectHooks() {
    ReversibleHooks::Install("CTxdStore", "PushCurrentTxd", 0x7316A0, &CTxdStore::PushCurrentTxd);
    ReversibleHooks::Install("CTxdStore", "PopCurrentTxd", 0x7316B0, &CTxdStore::PopCurrentTxd);
    ReversibleHooks::Install("CTxdStore", "FindTxdSlot_name", 0x731850, static_cast<int32_t (*)(const char*)>(&CTxdStore::FindTxdSlot));
    ReversibleHooks::Install("CTxdStore", "FindTxdSlot_hash", 0x7318E0, static_cast<int32_t (*)(uint32_t)>(&CTxdStore::FindTxdSlot));
    ReversibleHooks::Install("CTxdStore", "StartLoadTxd", 0x731930, &CTxdStore::StartLoadTxd);
    ReversibleHooks::Install("CTxdStore", "Create", 0x731990, &CTxdStore::Create);
    ReversibleHooks::Install("CTxdStore", "SetCurrentTxd", 0x7319C0, &CTxdStore::SetCurrentTxd);
    ReversibleHooks::Install("CTxdStore", "AddRef", 0x731A00, &CTxdStore::AddRef);
    ReversibleHooks::Install("CTxdStore", "RemoveRef", 0x731A30, &CTxdStore::RemoveRef);
    ReversibleHooks::Install("CTxdStore", "RemoveRefWithoutDelete", 0x731A70, &CTxdStore::RemoveRefWithoutDelete);
    ReversibleHooks::Install("CTxdStore", "GetNumRefs", 0x731AA0, &CTxdStore::GetNumRefs);
    ReversibleHooks::Install("CTxdStore", "AddTxdSlot", 0x731C80, &CTxdStore::AddTxdSlot);
    ReversibleHooks::Install("CTxdStore", "RemoveTxdSlot", 0x731CD0, &CTxdStore::RemoveTxdSlot);
    ReversibleHooks::Install("CTxdStore", "LoadTxd_stream", 0x731DD0, static_cast<bool (*)(int32_t, RwStream*)>(&CTxdStore::LoadTxd));
    ReversibleHooks::Install("CTxdStore", "LoadTxd_filename", 0x7320B0, static_cast<bool (*)(int32_t, const char*)>(&CTxdStore::LoadTxd));
    ReversibleHooks::Install("CTxdStore", "FinishLoadTxd", 0x731E40, &CTxdStore::FinishLoadTxd);
    ReversibleHooks::Install("CTxdStore", "RemoveTxd", 0x731E90, &CTxdStore::RemoveTxd);
    ReversibleHooks::Install("CTxdStore", "Initialise", 0x731F20, &CTxdStore::Initialise);
    ReversibleHooks::Install("CTxdStore", "Shutdown", 0x732000, &CTxdStore::Shutdown);
    ReversibleHooks::Install("CTxdStore", "GameShutdown", 0x732060, &CTxdStore::GameShutdown);
    ReversibleHooks::Install("CTxdStore", "GetParentTxdSlot", 0x408370, &CTxdStore::GetParentTxdSlot);
    ReversibleHooks::Install("CTxdStore", "GetTxd", 0x408340, &CTxdStore::GetTxd);
    ReversibleHooks::Install("CTxdStore", "TxdStoreFindCB", 0x731720, &CTxdStore::TxdStoreFindCB);
    ReversibleHooks::Install("CTxdStore", "TxdStoreLoadCB", 0x731710, &CTxdStore::TxdStoreLoadCB);
    ReversibleHooks::Install("CTxdStore", "SetupTxdParent", 0x731D50, &CTxdStore::SetupTxdParent);

    // global
    ReversibleHooks::Install("", "RemoveIfRefCountIsGreaterThanOne", 0x731680, &RemoveIfRefCountIsGreaterThanOne);
}

// initialise txd store
// 0x731F20
void CTxdStore::Initialise() {
    if (!ms_pTxdPool)
        ms_pTxdPool = new CPool<TxdDef>(TOTAL_TXD_MODEL_IDS, "TexDictionary");

    for (int32_t i = 0; i < 4; i++)
        defaultTxds[i] = static_cast<int16_t>(AddTxdSlot("*"));

    RwTextureSetFindCallBack(TxdStoreFindCB);
    RwTextureSetReadCallBack(TxdStoreLoadCB);
}

// shutdown txd store
// 0x732000
void CTxdStore::Shutdown() {
    delete ms_pTxdPool;
}

// 0x732060
void CTxdStore::GameShutdown() {
    for (int32_t i = 0; i < TOTAL_TXD_MODEL_IDS; i++) {
        TxdDef* txd = ms_pTxdPool->GetAt(i);
        if (!txd || txd->m_wRefsCount)
            continue;
        RemoveTxdSlot(i);
    }
}

// 0x731930
bool CTxdStore::StartLoadTxd(int32_t index, RwStream* stream) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    if (!txd || !RwStreamFindChunk(stream, rwID_TEXDICTIONARY, nullptr, nullptr))
        return false;

    RwTexDictionary* texdic = RwTexDictionaryGtaStreamRead1(stream);
    txd->m_pRwDictionary = texdic;
    return texdic != nullptr;
}

// 0x731E40
bool CTxdStore::FinishLoadTxd(int32_t index, RwStream* stream) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    if (!txd)
        return false;

    txd->m_pRwDictionary = RwTexDictionaryGtaStreamRead2(stream, txd->m_pRwDictionary);
    if (txd->m_pRwDictionary)
        SetupTxdParent(index);
    return txd->m_pRwDictionary != nullptr;
}

// load txd from stream
// 0x731DD0
bool CTxdStore::LoadTxd(int32_t index, RwStream* stream) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    if (!txd || !RwStreamFindChunk(stream, rwID_TEXDICTIONARY, nullptr, nullptr))
        return false;
    txd->m_pRwDictionary = RwTexDictionaryGtaStreamRead(stream);
    if (txd->m_pRwDictionary)
        SetupTxdParent(index);
    return txd->m_pRwDictionary != nullptr;
}

// load txd from file
// 0x7320B0
bool CTxdStore::LoadTxd(int32_t index, const char* filename) {
    char data[260];
    RwStream* stream;
    sprintf(data, "%s", filename);
    do {
        stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, data);
    } while (!stream);
    bool loaded = LoadTxd(index, stream);
    RwStreamClose(stream, nullptr);
    return loaded;
}

// store current txd
// 0x7316A0
void CTxdStore::PushCurrentTxd() {
    ms_pStoredTxd = RwTexDictionaryGetCurrent();
}

// restore txd
// 0x7316B0
void CTxdStore::PopCurrentTxd() {
    RwTexDictionarySetCurrent(ms_pStoredTxd);
    ms_pStoredTxd = nullptr;
}

// set the txd to work with
// 0x7319C0
void CTxdStore::SetCurrentTxd(int32_t index) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    if (txd)
        RwTexDictionarySetCurrent(txd->m_pRwDictionary);
}

// find txd by name. Returning value is txd index
// 0x731850
int32_t CTxdStore::FindTxdSlot(const char* name) {
    uint32_t key = CKeyGen::GetUppercaseKey(name);
    int32_t last = ms_lastSlotFound;

    for (; last >= 0; last--) {
        TxdDef* txd = ms_pTxdPool->GetAt(last);
        if (txd && txd->m_hash == key)
            break;
    }

    if (last < 0) {
        last = ms_lastSlotFound;
        for (last++;; last++) {
            if (last >= ms_pTxdPool->GetSize())
                return -1;

            TxdDef* txd = ms_pTxdPool->GetAt(last);
            if (txd && txd->m_hash == key)
                break;
        }
    }

    ms_lastSlotFound = last;
    return last;
}

// find txd by name hash. Returning value is txd index
// 0x7318E0
int32_t CTxdStore::FindTxdSlot(uint32_t hash) {
    for (int32_t i = 0; i < ms_pTxdPool->GetSize(); i++) {
        TxdDef* txd = ms_pTxdPool->GetAt(i);
        if (txd && txd->m_hash == hash)
            return i;
    }
    return -1;
}

// plugin-sdk has named it to getTexDictionary
// 0x408340
RwTexDictionary* CTxdStore::GetTxd(int32_t index) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    return txd ? txd->m_pRwDictionary : nullptr;
}

// plugin-sdk has named it to getTXDEntryParentIndex
// 0x408370
int32_t CTxdStore::GetParentTxdSlot(int32_t index) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    return txd ? txd->m_wParentIndex : -1;
}

// create rw tex dictionary for txd slot
// 0x731990
void CTxdStore::Create(int32_t index) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    if (txd)
        txd->m_pRwDictionary = RwTexDictionaryCreate();
}

// allocate new slot for this txd
// 0x731C80
int CTxdStore::AddTxdSlot(const char* name) {
    TxdDef* txd = ms_pTxdPool->New();
    txd->m_pRwDictionary = nullptr;
    txd->m_wRefsCount = 0;
    txd->m_wParentIndex = -1;
    txd->m_hash = CKeyGen::GetUppercaseKey(name);

    return ms_pTxdPool->GetIndex(txd);
}

// remove txd slot
// 0x731CD0
void CTxdStore::RemoveTxdSlot(int32_t index) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    if (!txd)
        return;

    if (txd->m_pRwDictionary)
        RwTexDictionaryDestroy(txd->m_pRwDictionary);
    ms_pTxdPool->Delete(txd);
}

// remove txd
// 0x731E90
void CTxdStore::RemoveTxd(int32_t index) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    if (!txd)
        return;

    if (txd->m_pRwDictionary) {
        RwTexDictionaryForAllTextures(txd->m_pRwDictionary, RemoveIfRefCountIsGreaterThanOne, nullptr);
        RwTexDictionaryDestroy(txd->m_pRwDictionary);
    }
    if (txd->m_wParentIndex != -1)
        RemoveRef(txd->m_wParentIndex);

    txd->m_pRwDictionary = nullptr;
}

// add reference for txd
// 0x731A00
void CTxdStore::AddRef(int32_t index) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    if (txd)
        txd->m_wRefsCount++;
}

// remove reference, if references count is 0, then delete txd
// 0x731A30
void CTxdStore::RemoveRef(int32_t index) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    if (!txd)
        return;

    if (--txd->m_wRefsCount <= 0)
        CStreaming::RemoveModel(index + RESOURCE_ID_TXD);
}

// remove reference without deleting
// 0x731A70
void CTxdStore::RemoveRefWithoutDelete(int32_t index) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    if (txd)
        txd->m_wRefsCount--;
}

// get references count
// 0x731AA0
int32_t CTxdStore::GetNumRefs(int32_t index) {
    TxdDef* txd = ms_pTxdPool->GetAt(index);
    return txd ? txd->m_wRefsCount : 0;
}

RwTexDictionary* CTxdStore::GetTxdParent(RwTexDictionary* txd) {
    return *PLUGINOFFSET(RwTexDictionary*, txd, TexDictionaryLinkPluginOffset);
}

void CTxdStore::SetTxdParent(RwTexDictionary* txd, RwTexDictionary* parent) {
    *PLUGINOFFSET(RwTexDictionary*, txd, TexDictionaryLinkPluginOffset) = parent;
}

// 0x731D50
void CTxdStore::SetupTxdParent(int32_t index) {
    TxdDef* txdcur = ms_pTxdPool->GetAt(index);
    if (!txdcur || txdcur->m_wParentIndex == -1)
        return;
    TxdDef* txdpar = ms_pTxdPool->GetAt(txdcur->m_wParentIndex);
    if (!txdpar)
        return;

    SetTxdParent(txdcur->m_pRwDictionary, txdpar->m_pRwDictionary);
    AddRef(txdcur->m_wParentIndex);
}

// 0x731720
RwTexture* CTxdStore::TxdStoreFindCB(const char* name) {
    RwTexDictionary* txd = RwTexDictionaryGetCurrent();
    for (; txd; txd = GetTxdParent(txd)) {
        RwTexture* tex = RwTexDictionaryFindNamedTexture(txd, name);
        if (tex)
            return tex;
    }
    return nullptr;
}

// 0x731710
RwTexture* CTxdStore::TxdStoreLoadCB(const char* name, const char* mask) {
    return nullptr;
}

// 0x731680
RwTexture* RemoveIfRefCountIsGreaterThanOne(RwTexture* texture, void* data) {
    if (texture->refCount > 1) {
        RwTextureDestroy(texture);
        RwTexDictionaryRemoveTexture(texture);
    }
    return texture;
}
