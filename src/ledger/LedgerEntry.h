#ifndef __LEDGERENTRY__
#define __LEDGERENTRY__

#include "ripple/types/api/base_uint.h"
#include "ripple_app/misc/SerializedLedger.h"
#include "LedgerDatabase.h"

using namespace ripple;
/*
LedgerEntry
Parent of AccountEntry, TrustLine, OfferEntry
*/
namespace stellar
{
    class LedgerEntry
    {
    protected:
        uint256 mIndex;
        SLE::pointer mSLE;

        virtual void insertIntoDB() = 0;
        virtual void updateInDB() = 0;
        virtual void deleteFromDB() = 0;

        virtual void calculateIndex() = 0;
    public:
        typedef std::shared_ptr<LedgerEntry> pointer;

        // calculate the index if you don't have it already
        uint256 getIndex();

        static LedgerEntry::pointer makeEntry(SLE::pointer sle);

        // these will do the appropriate thing in the DB and the preimage
        void storeDelete();
        void storeChange();
        void storeAdd();

        static void dropAll(LedgerDatabase &db); // deletes all data from DB
        static void appendSQLInit(vector<const char*> &init);
    };
}

#endif
