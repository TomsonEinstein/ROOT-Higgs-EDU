#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/TMVARegGui.h"

void TMVA_HZZ_Classification() {

   // options to control used methods

   bool useLikelihood = true;    // likelihood based discriminant
   bool useLikelihoodKDE = false;    // likelihood based discriminant
   bool useFischer = true;       // Fischer discriminant
   bool useMLP = true;          // Multi Layer Perceptron (old TMVA NN implementation)
   bool useBDT = true;           // Boosted Decision Tree
   bool useDL = false;            // TMVA Deep learning ( CPU or GPU)



   TMVA::Tools::Instance();

   auto outputFile = TFile::Open("TMVA_4lep.root", "RECREATE");

   TMVA::Factory factory("TMVA_HZZ_Classification", outputFile,
                         "!V:ROC:!Silent:Color:AnalysisType=Classification" );



// Setup Dataset(s)



   //input file path
   TString path  = "/home/tomson/root/develop/HZZAnalysis/data.4lep/";
   TString path2 = "/home/tomson/root/develop/HZZAnalysis/data.4lep/Additional 2lep MC/";
  
    // diboson
    TChain* chain_ZqqZll = new TChain("mini");
    chain_ZqqZll->AddFile(path+"MC/mc_363356.ZqqZll.4lep.root");
    TChain* chain_WqqZll = new TChain("mini");
    chain_WqqZll->AddFile(path2+"MC/mc_363358.WqqZll.2lep.root");
    TChain* chain_WpqqWmlv = new TChain("mini");
    chain_WpqqWmlv->AddFile(path2+"MC/mc_363359.WpqqWmlv.2lep.root");
    TChain* chain_WplvWmqq = new TChain("mini");
    chain_WplvWmqq->AddFile(path2+"MC/mc_363360.WplvWmqq.2lep.root");
    TChain* chain_WlvZqq = new TChain("mini");
    chain_WlvZqq->AddFile(path2+"MC/mc_363489.WlvZqq.2lep.root");
    TChain* chain_llll = new TChain("mini");
    chain_llll->AddFile(path+"MC/mc_363490.llll.4lep.root");
    TChain* chain_lllv = new TChain("mini");
    chain_lllv->AddFile(path+"MC/mc_363491.lllv.4lep.root");
    TChain* chain_llvv = new TChain("mini");
    chain_llvv->AddFile(path+"MC/mc_363492.llvv.4lep.root");
    TChain* chain_lvvv = new TChain("mini");
    chain_lvvv->AddFile(path2+"MC/mc_363493.lvvv.2lep.root");
    // Z+jets inclusive
    TChain* chain_Zee = new TChain("mini");
    chain_Zee->AddFile(path+"MC/mc_361106.Zee.4lep.root");
    TChain* chain_Zmumu = new TChain("mini");
    chain_Zmumu->AddFile(path+"MC/mc_361107.Zmumu.4lep.root");
    TChain* chain_Ztautau = new TChain("mini");
    chain_Ztautau->AddFile(path+"MC/mc_361108.Ztautau.4lep.root");
    //single top
    TChain* chain_single_top_tchan = new TChain("mini");
    chain_single_top_tchan->AddFile(path+"MC/mc_410011.single_top_tchan.4lep.root");
    TChain* chain_single_antitop_tchan = new TChain("mini");
    chain_single_antitop_tchan->AddFile(path+"MC/mc_410012.single_antitop_tchan.4lep.root");
    TChain* chain_single_top_schan = new TChain("mini");
    chain_single_top_schan->AddFile(path+"MC/mc_410025.single_top_schan.4lep.root");
    TChain* chain_single_antitop_schan = new TChain("mini");
    chain_single_antitop_schan->AddFile(path+"MC/mc_410026.single_antitop_schan.4lep.root");
    TChain* chain_single_top_wtchan = new TChain("mini");
    chain_single_top_wtchan->AddFile(path+"MC/mc_410013.single_top_wtchan.4lep.root");
    TChain* chain_single_antitop_wtchan = new TChain("mini");
    chain_single_antitop_wtchan->AddFile(path+"MC/mc_410014.single_antitop_wtchan.4lep.root");
    //ttbar
    TChain* chain_ttbar_lep = new TChain("mini");
    chain_ttbar_lep->AddFile(path+"MC/mc_410000.ttbar_lep.4lep.root");
    // W+jets inclusive
    TChain* chain_Wplusenu = new TChain("mini");
    chain_Wplusenu->AddFile(path2+"MC/mc_361100.Wplusenu.2lep.root");
    TChain* chain_Wplusmunu = new TChain("mini");
    chain_Wplusmunu->AddFile(path2+"MC/mc_361101.Wplusmunu.2lep.root");
    TChain* chain_Wplustaunu = new TChain("mini");
    chain_Wplustaunu->AddFile(path2+"MC/mc_361102.Wplustaunu.2lep.root");
    TChain* chain_Wminusenu = new TChain("mini");
    chain_Wminusenu->AddFile(path2+"MC/mc_361103.Wminusenu.2lep.root");
    TChain* chain_Wminusmunu = new TChain("mini");
    chain_Wminusmunu->AddFile(path2+"MC/mc_361104.Wminusmunu.2lep.root");
    TChain* chain_Wminustaunu = new TChain("mini");
    chain_Wminustaunu->AddFile(path2+"MC/mc_361105.Wminustaunu.2lep.root");
  // Higgs
  TChain* chain_ggH125_ZZ4lep = new TChain("mini");
  chain_ggH125_ZZ4lep->AddFile(path+"MC/mc_345060.ggH125_ZZ4lep.4lep.root");
  TChain* chain_ZH125_ZZ4lep = new TChain("mini");
  chain_ZH125_ZZ4lep->AddFile(path+"MC/mc_341947.ZH125_ZZ4lep.4lep.root");
  TChain* chain_WH125_ZZ4lep = new TChain("mini");
  chain_WH125_ZZ4lep->AddFile(path+"MC/mc_341964.WH125_ZZ4lep.4lep.root");
  TChain* chain_VBF125_ZZ4lep = new TChain("mini");
  chain_VBF125_ZZ4lep->AddFile(path+"MC/mc_344235.VBFH125_ZZ4lep.4lep.root");

// --- Register the training and test trees

   //get background trees

   TTree *bkg_llll1     = (TTree*)chain_llll->GetEntries();
   TTree *bkg_lllv1     = (TTree*)chain_lllv->GetEntries();
   TTree *bkg_llvv1     = (TTree*)chain_llvv->GetEntries();
   TTree *bkg_lvvv1     = (TTree*)chain_lvvv->GetEntries();
   TTree *bkg_single_antitop_schan1    = (TTree*)chain_single_antitop_schan->GetEntries();
   TTree *bkg_single_antitop_tchan1     = (TTree*)chain_single_antitop_tchan->GetEntries();
   TTree *bkg_single_antitop_wtchan1     = (TTree*)chain_single_antitop_wtchan->GetEntries();
   TTree *bkg_single_top_schan1     = (TTree*)chain_single_top_schan->GetEntries();
   TTree *bkg_single_top_tchan1     = (TTree*)chain_single_top_tchan->GetEntries();
   TTree *bkg_single_top_wtchan1    = (TTree*)chain_single_top_wtchan->GetEntries();
   TTree *bkg_ttbar_lep1     = (TTree*)chain_ttbar_lep->GetEntries();
   TTree *bkg_WlvZqq1    = (TTree*)chain_WlvZqq->GetEntries();
   TTree *bkg_Wminusmunu1     = (TTree*)chain_Wminusmunu->GetEntries();
   TTree *bkg_Wminustaunu1    = (TTree*)chain_Wminustaunu->GetEntries();
   TTree *bkg_Wplusenu1    = (TTree*)chain_Wplusenu->GetEntries();
   TTree *bkg_Wplusmunu1     = (TTree*)chain_Wplusmunu->GetEntries();
   TTree *bkg_Wplustaunu1     = (TTree*)chain_Wplustaunu->GetEntries();
   TTree *bkg_WplvWmqq1     = (TTree*)chain_WplvWmqq->GetEntries();
   TTree *bkg_WpqqWmlv1     = (TTree*)chain_WpqqWmlv->GetEntries();
   TTree *bkg_WqqZll1    = (TTree*)chain_WqqZll->GetEntries();
   TTree *bkg_Zee1     = (TTree*)chain_Zee->GetEntries();
   TTree *bkg_Zmumu1     = (TTree*)chain_Zmumu->GetEntries();
   TTree *bkg_ZqqZll1     = (TTree*)chain_ZqqZll->GetEntries();
   TTree *bkg_Ztautau1    = (TTree*)chain_Ztautau->GetEntries();

   //get signal trees

   TTree *sig_ggH125_ZZ4lep1 = (TTree*)chain_ggH125_ZZ4lep->GetEntries();
   TTree *sig_ZH125_ZZ4lep1 = (TTree*)chain_ZH125_ZZ4lep->GetEntries();
   TTree *sig_VBF125_ZZ4lep1     = (TTree*)chain_VBF125_ZZ4lep->GetEntries();
   TTree *sig_WH125_ZZ4lep1    = (TTree*)chain_WH125_ZZ4lep->GetEntries();

   //input background trees

   TTree *bkg_llll     = (TTree*)chain_llll->GetTree();
   TTree *bkg_lllv     = (TTree*)chain_lllv->GetTree();
   TTree *bkg_llvv     = (TTree*)chain_llvv->GetTree();
   TTree *bkg_lvvv     = (TTree*)chain_lvvv->GetTree();
   TTree *bkg_single_antitop_schan     = (TTree*)chain_single_antitop_schan->GetTree();
   TTree *bkg_single_antitop_tchan     = (TTree*)chain_single_antitop_tchan->GetTree();
   TTree *bkg_single_antitop_wtchan     = (TTree*)chain_single_antitop_wtchan->GetTree();
   TTree *bkg_single_top_schan     = (TTree*)chain_single_top_schan->GetTree();
   TTree *bkg_single_top_tchan     = (TTree*)chain_single_top_tchan->GetTree();
   TTree *bkg_single_top_wtchan     = (TTree*)chain_single_top_wtchan->GetTree();
   TTree *bkg_ttbar_lep     = (TTree*)chain_ttbar_lep->GetTree();
   TTree *bkg_WlvZqq     = (TTree*)chain_WlvZqq->GetTree();
   TTree *bkg_Wminusmunu     = (TTree*)chain_Wminusmunu->GetTree();
   TTree *bkg_Wminustaunu    = (TTree*)chain_Wminustaunu->GetTree();
   TTree *bkg_Wplusenu     = (TTree*)chain_Wplusenu->GetTree();
   TTree *bkg_Wplusmunu     = (TTree*)chain_Wplusmunu->GetTree();
   TTree *bkg_Wplustaunu     = (TTree*)chain_Wplustaunu->GetTree();
   TTree *bkg_WplvWmqq     = (TTree*)chain_WplvWmqq->GetTree();
   TTree *bkg_WpqqWmlv     = (TTree*)chain_WpqqWmlv->GetTree();
   TTree *bkg_WqqZll    = (TTree*)chain_WqqZll->GetTree();
   TTree *bkg_Zee     = (TTree*)chain_Zee->GetTree();
   TTree *bkg_Zmumu     = (TTree*)chain_Zmumu->GetTree();
   TTree *bkg_ZqqZll     = (TTree*)chain_ZqqZll->GetTree();
   TTree *bkg_Ztautau    = (TTree*)chain_Ztautau->GetTree();

   //input signal trees

   TTree *sig_VBF125_ZZ4lep     = (TTree*)chain_VBF125_ZZ4lep->GetTree();
   TTree *sig_WH125_ZZ4lep    = (TTree*)chain_WH125_ZZ4lep->GetTree();
   TTree *sig_ggH125_ZZ4lep = (TTree*)chain_ggH125_ZZ4lep->GetTree();
   TTree *sig_ZH125_ZZ4lep = (TTree*)chain_ZH125_ZZ4lep->GetTree();


// Declare DataLoader(s)



   TMVA::DataLoader * loader = new TMVA::DataLoader("dataset");

   loader->AddSpectator("runNumber");
   loader->AddSpectator("eventNumber");
   loader->AddSpectator("mcWeight");
   loader->AddSpectator("scaleFactor_PILEUP");
   loader->AddSpectator("scaleFactor_ELE");
   loader->AddSpectator("scaleFactor_MUON");
   loader->AddSpectator("scaleFactor_PHOTON");
   loader->AddSpectator("scaleFactor_TAU");
   loader->AddSpectator("scaleFactor_BTAG");
   loader->AddSpectator("scaleFactor_LepTRIGGER");
   loader->AddSpectator("scaleFactor_PhotonTRIGGER");
   //loader->AddSpectator("scaleFactor_TauTRIGGER");
   //loader->AddSpectator("scaleFactor_DiTauTRIGGER");
   loader->AddSpectator("trigE");
   loader->AddSpectator("trigM");
   loader->AddSpectator("trigP");
   //loader->AddSpectator("trigT");
   //loader->AddSpectator("trigDT");
   loader->AddSpectator("lep_n");
   loader->AddSpectator("lep_truthMatched");
   loader->AddSpectator("lep_trigMatched");
   loader->AddVariable("lep_pt[0]");
   loader->AddVariable("lep_pt[1]");
   loader->AddVariable("lep_pt[2]");
   loader->AddVariable("lep_pt[3]");
   loader->AddVariable("lep_eta[0]");
   loader->AddVariable("lep_eta[1]");
   loader->AddVariable("lep_eta[2]");
   loader->AddVariable("lep_eta[3]");
   loader->AddVariable("lep_phi[0]");
   loader->AddVariable("lep_phi[1]");
   loader->AddVariable("lep_phi[2]");
   loader->AddVariable("lep_phi[3]");
   loader->AddVariable("lep_E[0]");
   loader->AddVariable("lep_E[1]");
   loader->AddVariable("lep_E[2]");
   loader->AddVariable("lep_E[3]");
   loader->AddSpectator("lep_z0");
   loader->AddSpectator("lep_charge");
   loader->AddSpectator("lep_type");
   loader->AddSpectator("lep_isTightID");
   loader->AddSpectator("lep_ptcone30");
   loader->AddSpectator("lep_etcone20[0]");
   loader->AddVariable("lep_etcone20[1]");
   loader->AddVariable("lep_etcone20[2]");
   loader->AddVariable("lep_etcone20[3]");
   //loader->AddSpectator("lep_tackd0pvunbiased");
   loader->AddSpectator("lep_tracksigd0pvunbiased");
   loader->AddSpectator("met_et");
   loader->AddSpectator("met_phi");
   loader->AddSpectator("jet_n");
   loader->AddVariable("jet_pt[0]");
   loader->AddVariable("jet_pt[1]");
   loader->AddSpectator("jet_eta");
   loader->AddSpectator("jet_phi");
   loader->AddVariable("jet_E[0]");
   loader->AddVariable("jet_E[1]");
   loader->AddSpectator("jet_jvt");
   loader->AddSpectator("jet_trueflav");
   loader->AddSpectator("jet_truthMatched");
   loader->AddVariable("jet_MV2c10[0]");
   loader->AddVariable("jet_MV2c10[1]");
   loader->AddSpectator("lep_pt_syst");
   loader->AddSpectator("met_et_syst");
   loader->AddSpectator("jet_pt_syst");
/// We set now the input data trees in the TMVA DataLoader class

// global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

// You can add an arbitrary number of signal or background trees
   loader->AddBackgroundTree    ( bkg_llll,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_lllv,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_llvv,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_lvvv,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_single_antitop_schan,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_single_antitop_tchan,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_single_antitop_wtchan,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_single_top_schan,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_single_top_tchan,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_single_top_wtchan,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_ttbar_lep,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_WlvZqq,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_Wminusmunu,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_Wminustaunu,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_Wplusenu,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_Wplusmunu,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_Wplustaunu,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_WplvWmqq,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_WpqqWmlv,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_WqqZll,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_Zee,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_Zmumu,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_ZqqZll,     backgroundWeight     );
   loader->AddBackgroundTree    ( bkg_Ztautau,     backgroundWeight     );

   loader->AddSignalTree    ( sig_VBF125_ZZ4lep,     signalWeight     );
   loader->AddSignalTree    ( sig_WH125_ZZ4lep,     signalWeight     );
   loader->AddSignalTree    ( sig_ggH125_ZZ4lep,     signalWeight     );
   loader->AddSignalTree    ( sig_ZH125_ZZ4lep,     signalWeight     );
   

// Set individual event weights (the variables must exist in the original TTree)
   loader->SetSignalWeightExpression    ("abs(scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER*scaleFactor_PILEUP*mcWeight)");
   loader->SetBackgroundWeightExpression("abs(scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER*scaleFactor_PILEUP*mcWeight)");

// Apply additional cuts on the signal and background samples (can be different)
   // TCut mycuts = ; // for example: 
   TCut bkg = "";
   // TCut mycutb = ; // for example: 
   TCut sig = "";

   loader->PrepareTrainingAndTestTree( bkg, sig,
                                       "SplitMode=Random:NormMode=NumEvents:!V" );


// Booking Methods

// Likelihood ("naive Bayes estimator")
if (useLikelihood) {
   factory.BookMethod(loader, TMVA::Types::kLikelihood, "Likelihood",
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );
}
// Use a kernel density estimator to approximate the PDFs
if (useLikelihoodKDE) {
   factory.BookMethod(loader, TMVA::Types::kLikelihood, "LikelihoodKDE",
                      "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" );

}

// Fisher discriminant (same as LD)
if (useFischer) {
   factory.BookMethod(loader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
}

//Boosted Decision Trees
if (useBDT) {
   factory.BookMethod(loader,TMVA::Types::kBDT, "BDT",
                      "!V:NTrees=200:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
}

//Multi-Layer Perceptron (Neural Network)
if (useMLP) {
   factory.BookMethod(loader, TMVA::Types::kMLP, "MLP",
                      "!H:!V:NeuronType=tanh:VarTransform=N:NCycles=100:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
}

// Deep Learning

   if (useDL) {

      bool useDLGPU = false;
#ifdef R__HAS_TMVAGPU
      useDLGPU = true;
#endif

      // Define DNN layout
      TString inputLayoutString = "InputLayout=1|1|7";
      TString batchLayoutString= "BatchLayout=1|128|7";
      TString layoutString ("Layout=DENSE|64|TANH,DENSE|64|TANH,DENSE|64|TANH,DENSE|64|TANH,DENSE|1|LINEAR");
      // Define Training strategies
      // one can catenate several training strategies
      TString training1("LearningRate=1e-3,Momentum=0.9,"
                        "ConvergenceSteps=10,BatchSize=128,TestRepetitions=1,"
                        "MaxEpochs=30,WeightDecay=1e-4,Regularization=None,"
                        "Optimizer=ADAM,ADAM_beta1=0.9,ADAM_beta2=0.999,ADAM_eps=1.E-7," // ADAM default parameters
                        "DropConfig=0.0+0.0+0.0+0.");
      //     TString training2("LearningRate=1e-3,Momentum=0.9"
      //                       "ConvergenceSteps=10,BatchSize=128,TestRepetitions=1,"
      //                       "MaxEpochs=20,WeightDecay=1e-4,Regularization=None,"
      //                       "Optimizer=SGD,DropConfig=0.0+0.0+0.0+0.");

      TString trainingStrategyString ("TrainingStrategy=");
      trainingStrategyString += training1; // + "|" + training2;

      // General Options.

      TString dnnOptions ("!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=G:"
                          "WeightInitialization=XAVIER");
      dnnOptions.Append (":"); dnnOptions.Append (inputLayoutString);
      dnnOptions.Append (":"); dnnOptions.Append (batchLayoutString);
      dnnOptions.Append (":"); dnnOptions.Append (layoutString);
      dnnOptions.Append (":"); dnnOptions.Append (trainingStrategyString);

      TString dnnMethodName = "DNN_CPU";
      if (useDLGPU) {
         dnnOptions += ":Architecture=GPU";
         dnnMethodName = "DNN_GPU";
      } else  {
         dnnOptions += ":Architecture=CPU";
      }

      factory.BookMethod(loader, TMVA::Types::kDL, dnnMethodName, dnnOptions);

   }
   factory.TrainAllMethods();

   factory.TestAllMethods();

   factory.EvaluateAllMethods();

   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;
}
