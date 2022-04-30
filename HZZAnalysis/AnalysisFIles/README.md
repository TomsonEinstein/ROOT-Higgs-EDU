# README

This code originally comes from CERN website.So it's illegal to use it to publish academic results.But it is valuable to Learn from it to write your own code.

Important documentation:
https://cds.cern.ch/record/2707171

## Contents

 - main_HZZ:TChain to add the data and Process to compile and run the data

 - HZZAnalysis:The core code to analysis data

 - HZZAnalysis.h:

 - HZZAnalysisHistogram.h:

They will be explained further in the source code.

## Physics examples of HZZAnalysis

Example of physics analysis: the case of SM Higgs boson production in the H → ZZ decay channel in the four-lepton final state

The search for the SM Higgs boson through the decay H → ZZ → 4l, where l = e or μ, represents the so called "golden channel" and leads to a narrow four-lepton invariant-mass peak on top a relatively smooth and small background, largely due to the excellent momentum resolution of the ATLAS detector. The Higgs-boson decay branching ratio to the four-lepton final state for the Higgs boson mass of 125 GeV is predicted to be 0.0124% //标准模型计算出来的四轻子末态衰变产率 in the SM, and the expected cross section times branching ratio for the process H → ZZ → 4l is 2.9 fb at 13 TeV // 通量 . Hence, based on an integrated luminosity // 积分照度 of the current ATLAS Open Data set of 10/fb, one expects a total of 29 events to have been produced in the four-lepton final state (before reconstruction and event selection).

In order to identify these events, one needs to apply the **standard object-selection criteria** (defined in "Reconstructed physics objects") with a loose lepton pT requirement and loose lepton calorimeter- and track-based isolation requirements, and an event-selection criteria defined as:

![图片](http://opendata.atlas.cern/release/2020/documentation/physics/pictures/FL2.png "FL2")

At the end, one is able to compare data and MC prediction for the distribution of e.g. the four-lepton invariant mass, as seen below. An excess of events in the distribution of the four-lepton invariant mass near 125 GeV is observed, which corresponds to the expected in the SM production of the Higgs boson.

![图片](http://opendata.atlas.cern/release/2020/documentation/physics/pictures/fig_09h.png "fig_09h")

