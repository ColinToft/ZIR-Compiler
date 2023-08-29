#ifndef __ANALYSIS_MANAGER_H
#define __ANALYSIS_MANAGER_H

#include <unordered_map>

#include "Analysis.h"
#include "AnalysisManagerProxy.h"
#include "AnalysisPass.h"
#include "backend/MachineFunction.h"
#include "backend/MachineModule.h"

enum AnalysisManagerProxyID;

template <typename IRUnitT> class AnalysisManager {

  public:
    AnalysisManager() {}

    virtual ~AnalysisManager() {}

    void registerAnalysisPass(AnalysisPass<IRUnitT> *analysisPass) {
        analysisPasses[analysisPass->getID()] = analysisPass;
    }

    void registerAnalysisManagerProxy(AnalysisManagerProxyID proxyID,
                                      Analysis *proxy) {
        proxyMap[proxyID] = proxy;
    }

  private:
    /**
     * Gets the analysis pass with the given ID.
     *
     */
    Analysis *getAnalysisWithID(IRUnitT *IR, AnalysisID id) {
        // First, see if the IR unit has any analyses.
        auto unitAnalyses = availableAnalyses.find(IR);
        if (unitAnalyses == availableAnalyses.end()) {
            Analysis *analysis = lookupPass(id)->run(IR);
            // Add the analysis to the IR unit's analyses.
            availableAnalyses[IR][id] = analysis;
            return analysis;
        }

        // Next, see if the IR unit has the analysis we're looking for.
        auto analysis = unitAnalyses->second.find(id);
        if (analysis == unitAnalyses->second.end()) {
            // If not, run the analysis pass and add it to the IR unit's
            // analyses.
            Analysis *analysis = lookupPass(id)->run(IR);
            availableAnalyses[IR][id] = analysis;
            return analysis;
        }
        // If so, return it.
        return analysis->second;
    }

    Analysis *getAnalysisManagerProxy(AnalysisManagerProxyID proxyID) {
        auto proxy = proxyMap.find(proxyID);
        if (proxy == proxyMap.end()) {
            std::cerr << "No proxy with ID " << proxyID << std::endl;
            exit(1);
        }

        return proxy->second;
    }

    template <typename TargetManagerIRUnitT>
    AnalysisManagerProxy<IRUnitT, TargetManagerIRUnitT> *
    getAnalysisManagerProxy() {
        AnalysisManagerProxyID proxyID;
        if (std::is_same<IRUnitT, MachineModule>::value &&
            std::is_same<TargetManagerIRUnitT, MachineFunction>::value) {
            proxyID = AnalysisManagerProxyID::
                MachineModuleAnalysisManagerMachineFunctionProxyID;
        } else if (std::is_same<IRUnitT, MachineFunction>::value &&
                   std::is_same<TargetManagerIRUnitT, MachineModule>::value) {
            proxyID = AnalysisManagerProxyID::
                MachineFunctionAnalysisManagerMachineModuleProxyID;
        } else {
            std::cerr << "No proxy for analysis manager of type "
                      << typeid(IRUnitT).name()
                      << " to analysis manager of type "
                      << typeid(TargetManagerIRUnitT).name() << std::endl;
            exit(1);
        }

        return (AnalysisManagerProxy<IRUnitT, TargetManagerIRUnitT> *)
            getAnalysisManagerProxy(proxyID);
    }

    /**
     * Gets the analysis pass with the given ID.
     *
     */
    AnalysisPass<IRUnitT> *lookupPass(AnalysisID id) {
        auto analysisPass = analysisPasses.find(id);
        if (analysisPass == analysisPasses.end()) {
            std::cerr << "No analysis pass with ID " << id << std::endl;
            exit(1);
        }

        return analysisPass->second;
    }

  public:
    template <typename AnalysisT> AnalysisT *getAnalysis(IRUnitT *IR) {
        return (AnalysisT *)getAnalysisWithID(IR, AnalysisT::ID);
    }

    template <typename TargetManagerIRUnitT>
    AnalysisManager<TargetManagerIRUnitT> &getAnalysisManager() {
        return getAnalysisManagerProxy<TargetManagerIRUnitT>()->getManager();
    }

  private:
    std::unordered_map<IRUnitT *, std::unordered_map<AnalysisID, Analysis *>>
        availableAnalyses;

    std::unordered_map<AnalysisID, AnalysisPass<IRUnitT> *> analysisPasses;

    std::unordered_map<AnalysisManagerProxyID, Analysis *> proxyMap;
};

typedef AnalysisManager<MachineModule> MachineModuleAnalysisManager;
typedef AnalysisManager<MachineFunction> MachineFunctionAnalysisManager;

#endif // __ANALYSIS_MANAGER_H