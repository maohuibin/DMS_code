#ifndef HHSEQUENCEMGR_H
#define HHSEQUENCEMGR_H

#include <string>
#include <vector>
#include <map>
#include <stdint.h>

class HHCommandBase;

class HHSequence
{
public:
    HHSequence(const std::string& name);
    virtual ~HHSequence();

    std::string name();
    bool isShown();
    void setShow(bool bShow);
    bool isAdvanced();
    void setAdvanced(bool bAdvanced);
    void addCommand(HHCommandBase* pCmd);
    void setNext(const std::string& nextName);
    std::string getNext();
    virtual bool fire();

private:
    std::string mName;
    std::string mNext;
    bool mShow;
    bool mAdvanced;

protected:
    std::vector<HHCommandBase*> mCommands;
};

class HHSequenceSlider : public HHSequence
{
public:
    HHSequenceSlider(const std::string& name, uint32_t min, uint32_t max, uint32_t step);

    uint32_t getMax();
    uint32_t getMin();
    uint32_t getValue();
    uint32_t getStep();
    void setValue(uint32_t value);

    bool fireWithArg(uint32_t newValue);

private:
    uint32_t mMin;
    uint32_t mMax;
    uint32_t mValue;
    uint32_t mStep;
};

class HHSequenceMgr
{
public:
    HHSequenceMgr();
    ~HHSequenceMgr();

    bool parseCommandList();
    bool parseSequenceList();
    bool parseSliderList();

    HHCommandBase* getCommandByName(const std::string& name);
    HHSequence* getSequenceByName(const std::string& name);
    HHSequenceSlider* getSliderByName(const std::string& name);

    std::vector<std::string> getAllSequenceNames();
    std::vector<std::string> getAllSliderNames();

private:
    std::vector<HHCommandBase*>           mCommandList;
    std::map<std::string, HHCommandBase*> mCommandMap;
    std::vector<HHSequence*>              mSequenceList;
    std::map<std::string, HHSequence*>    mSequenceMap;
    std::vector<HHSequence*>              mSliderList;
    std::map<std::string, HHSequence*>    mSliderMap;
};

#endif // HHSEQUENCEMGR_H
