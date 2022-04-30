# README

This code originally comes from CERN website.So it's illegal to use it to publish academic results.But it is valuable to Learn from it to write your own code.

Important documentation:
https://cds.cern.ch/record/2707171

## Contents
### The Analysis Part
Each analysis sub-folder contains the following files:

 - analysis main code (NNAnalysis.C): it makes all the selection and stores the output histograms;
 -  analysis main header (NNAnalysis.h): it defines the histograms and gives access to the variables stored in the input samples;
 -  histogram header (NNAnalysisHistograms.h): it defines the name of output histograms;
 -  analysis main-control code (main_NNAnalysis.C): it controls which input samples are going to be used and their location;
 -  a bash script (run.sh), executed via a Linux/UNIX shell called source: helps you in running the analysis interactively.
 -  in case you used the welcome script, the output directory (Output_NNAnalysis) will be created: this is the place where the output of the analysis code (one file with histograms per each input sample) will be stored. Warning: if the output directory does not exist, the code will fail, please create always an empty one!

### The Plotting Part
The folder /Plotting

 - plotting main code (Plotting.cxx): it makes all plot magic and controls automatically what to do for each of the 12 analyses;
 - plotting main header (Plotting.h): it defines all the needed bits and pieces for the plotting code;
 -  helper directory (list_histos): inside it you will find 12 control files with names HistoList_ANALYSISNAME.txt, each of these controls which histograms are going to be used and plotted for each analysis;
 -  helper directory (inputfiles): inside it you will find 12 control files with names Files_ANALYSISNAME.txt, each of these controls which input samples exactly are going to be used for this particular analysis, their cross-section and sum of weights. DO NOT CHANGE!!!
 -  bash script (plotme.sh): helps you in running the plotting code interactively, please use it!
 -  a makefile (Makefile): a set of directives used by a make build automation tool to generate the output executable;
 -  in case you used the welcome script, the output directory (histograms): it will contain the output plots! Do not forget to rename it in case you run over several analyses!



## Physics examples of HZZAnalysis

Example of physics analysis: the case of SM Higgs boson production in the H → ZZ decay channel in the four-lepton final state

The search for the SM Higgs boson through the decay H → ZZ → 4l, where l = e or μ, represents the so called "golden channel" and leads to a narrow four-lepton invariant-mass peak on top a relatively smooth and small background, largely due to the excellent momentum resolution of the ATLAS detector. The Higgs-boson decay branching ratio to the four-lepton final state for the Higgs boson mass of 125 GeV is predicted to be 0.0124% //标准模型计算出来的四轻子末态衰变产率 in the SM, and the expected cross section times branching ratio for the process H → ZZ → 4l is 2.9 fb at 13 TeV // 通量 . Hence, based on an integrated luminosity // 积分照度 of the current ATLAS Open Data set of 10/fb, one expects a total of 29 events to have been produced in the four-lepton final state (before reconstruction and event selection).

In order to identify these events, one needs to apply the **standard object-selection criteria** (defined in "Reconstructed physics objects") with a loose lepton pT requirement and loose lepton calorimeter- and track-based isolation requirements, and an event-selection criteria defined as:

![图片](http://opendata.atlas.cern/release/2020/documentation/physics/pictures/FL2.png "FL2")

At the end, one is able to compare data and MC prediction for the distribution of e.g. the four-lepton invariant mass, as seen below. An excess of events in the distribution of the four-lepton invariant mass near 125 GeV is observed, which corresponds to the expected in the SM production of the Higgs boson.

![图片](http://opendata.atlas.cern/release/2020/documentation/physics/pictures/fig_09h.png "fig_09h")

## C++ Based Framework
http://opendata.atlas.cern/release/2020/documentation/frameworks/cpp.html

## Data Visualization

http://opendata.atlas.cern/release/2020/documentation/visualization/index.html

## Glossary

Below a few ATLAS physics terms are explained. This is not intended to be an exhaustive glossary, more detailed answers might be found using the search engine located in the upper right corner of this page or at the official ATLAS Collaboration and CERN websites.
### Detector layout
![图片](http://opendata.atlas.cern/release/2020/documentation/atlas/pictures/ATLASImage.jpg "Dectector Layout")


The ATLAS detector has a layout that is typical for a collider detector. There are two types of detector components: tracking detectors, which measure the position of a crossing charged particle with minimal disturbance, and calorimeters, which measure the energy of a particle by total absorption.

Travelling from the collision point outwards there exist tracking detectors (inner detector), then calorimeters (electromagnetic and hadronic) and then more tracking detectors (muon spectrometer).

The complete ATLAS detector is split into a barrel part, where detector layers are positioned on cylindrical surfaces around the beam axis, and two end-cap parts, where detector layers are positioned in planes of constant z perpendicular to the beam pipe.
### Antimatter

A particle and its antiparticle have the same mass as one another, but opposite electric charge and other quantum numbers. A collision between any particle and its antiparticle partner leads to their mutual annihilation, giving rise to various proportions of photons, neutrinos, and sometimes less massive particle–antiparticle pairs.
### ATLAS coordinate system

ATLAS uses a right-handed coordinate system with its origin at the nominal interaction point (IP) in the centre of the detector. The positive x-axis is defined by the direction from the IP to the centre of the LHC ring, with the positive y-axis pointing upwards, while the beam direction defines the z-axis. Cylindrical coordinates (r, ϕ) are used in the transverse plane, ϕ being the azimuthal angle around the z-axis. The ATLAS detector design is symmetrical in ϕ.
### Beam

The particles in an accelerator are grouped together in a beam. Beams can contain billions of particles and can be divided into discrete portions called bunches. Each bunch is typically several centimetres long and just a few microns wide.
Branching fraction

In general, a particle can decay in several modes (see "decay channel"). For example, a Z-boson can decay into a pair of neutrinos, a pair of charged leptons, or a pair of quarks (i.e., all the standard model fermions lighter than half the Z-boson mass). The probability for a Z-boson to decay into a neutrino pair is about 20%, into a pair of charged leptons (electrons, muons, or taus) is about 10%, and into a pair of quarks (u,d,c,s,b) is about 70%. These probabilities are called branching fractions.
### Cross-section

The cross-section is a measure of the probability for that process to occur during any proton-proton collision. Processes with larger cross-sections occur more often than processes with small cross-sections.
### Decay channel

Particles decay into other particles over time. Decay channels are the possible transformations a particle can undergo as it decays. For example, the Higgs could decay into several different channels, such as two photons or two W bosons or two Z bosons.
### Electron-volt (eV)

One electron volt is equal to ~1.6 X 10^-19 joules. MeV (10^6) and TeV (10^12) are units of energy used in particle physics. 1 TeV is about the energy of motion of a flying mosquito.
### Event

An event is a snapshot of a collision in the LHC. Highly energetic collisions can create particles more massive (energy-mass equivalence) than those involved in the collisions (protons, in the case of the LHC). These massive particles quickly decay into lighter stable particles. Physicists study the decay products of collisions to determine what particles were created in the events.
### Excess

When scientists observe more of a certain type of event than expected in a data plot, they call that an excess. Scientists measure the statistical significance (see "Standard deviation") of excesses to determine how certain they are that they result from new physics and not simply random fluctuations.
### Fermions and bosons

A subatomic particle, such as a nucleon, which has half-integral spin and follows a statistical description given by Fermi and Dirac is called a "fermion". A "boson" is a subatomic particle, such as a photon, which has zero or integral spin and follows a statistical description given by Bose and Einstein.
### Fundamental particles and forces

Fundamental particles are the building blocks of matter as they are all indivisible. All other particles are therefore a combination of the fundamental particles. The fundamental forces, explain the interactions between particles in our universe. These forces are gravity, electromagnetism, the strong and the weak force. Electromagnetism and the weak force are linked through the electroweak theory.
### Good run list

Good run lists are the way to select good data samples for physics analysis. There are a number of ways the data may not be good e.g the LHC is not in stable-beam mode, the magnets are off, some of the sub-detectors are switched off.
### Invariant mass

Particle physicists use the word "mass" to refer to the quantity (sometimes called "rest mass") which is proportional to the inertia of the particle when it is at rest. When a particle decays and hence no longer exists, its mass before the decay can be calculated from the energies and momenta of the decay products. The inferred value of the mass is independent of the reference frame in which the energies and momenta are measured, so that that the mass called "invariant".
### Isolation

An object isolation is an important feature, because it indicates where the object (lepton, jet,..) stems from. As an example, an isolated electron is likely to originate from a Z-boson, W-boson or tau-lepton. In contrast, a non-isolated electron is likely to originate from a b-hadron or c-hadron decay.
### Jets

Jets are the dominant final state objects of high-energy proton-proton interactions at the LHC. They are key ingredients for many physics measurements and for searches for new phenomena. Jets are observed as groups of topologically-related energy deposits in the ATLAS calorimeters, most of which are associated with tracks of charged particles as measured in the inner detector. They are reconstructed and calibrated using a combination of methods based on simulation and data-driven techniques.

Jet cleaning criteria have been developed in order to identify fake jets which arise due to noise or to out-of-time energy depositions. Jets failing these criteria are flagged as either "bad", likely to be fake, or "ugly", likely to be mismeasured due to falling into less well instrumented regions.
### Jet vertex tagger (JVT)

The Jet Vertex Tagger can be used to suppress pileup jets, and is a crucial component of many physics analyses using LHC pp collision. In ATLAS, tracking information has been used to calculate a variable called the jet-vertex-fraction, which is the fraction of the total momentum of tracks in the jet which is associated with the primary vertex.
### Monte-Carlo (MC) samples

Monte-Carlo event generators is a computer program designed to simulate the final states of high-energy collisions in full detail down to the level of individual stable particles. The aim is to generate a large number of simulated collision events, each consisting of a list of final-state particles and their momenta, such that the probability to produce an event with a given list is proportional (approximately) to the probability that the corresponding actual event is produced in the real world. The Monte Carlo method makes use of pseudorandom numbers to simulate the event-to-event fluctuations intrinsic to quantum processes.
### Opening angle (ΔR)

The opening angle (also called angular separation) between physics objects e.g. a lepton and a jet, can be important in understanding or identifying different physics processes. It is calculated as a function of η and φ, and defined as: $ΔR=\sqrt{(Δη)^2+(Δϕ)^2}$.
### Parton Distribution Functions

The momentum distribution functions of the partons (quarks and gluons) within the proton are called Parton Distribution Functions.
Pseudorapidity (η)

A parameter (denoted by η) frequently used in colliding beam experiments to express angles with respect to the axis of the colliding beams. It has the value 0 for particle trajectories that are perpendicular to the beam, and positive or negative values for those at an angle to the beam.
Resolution

Measure of the accuracy of a detector measurement, e.g. of energy or spatial position.
### Signal and background

When searching for signs of new physics, physicists compare what they observe to what theories predict they will observe. The background is the set of results scientists expect to see. If an experiment sees more instances of a certain type of event (see "excess") than they expect to see as part of the background, it might be evidence of new physics. The specific physics process ("signal") events and all the other "background" events can be generated using Monte Carlo generators. After that, the analysis selection is built in order to rejecting as much background as possible, so that the desired physics processes can be observed. Data events in principle contain both signal and background events.
### Standard deviation

A standard deviation is a measure of how unusual a set of data is if a hypothesis is true. Physicists express standard deviations in units called "sigma". The higher the number of sigma, the more incompatible the data are with the hypothesis. If the data are incompatible enough with a hypothesis that says the experiment will find only background (see "Background"), that could constitute a discovery.
### Transverse momentum (pT)

The term pT stands for transverse momentum, the component of momentum perpendicular to the beam line. In proton-proton collisions the overall momentum along the beamline is not known. This is due to the fact that the protons are composite particles consisting of many partons (quarks and gluons). When two protons collide it is actually the partons that interact. Each of the partons carries an unknown fraction of the protons momentum. So their exact momentum along the beamline is unknown. We only know that the overall momentum perpendicular to the beamline is zero before the collision. Thus, the transverse momentum is the most important momentum variable in a proton-proton collision.
### Vectorial sum

A vectorial sum is the result of adding two or more vectors together via vector addition.