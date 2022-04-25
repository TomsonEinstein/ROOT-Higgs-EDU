void write(TString filename)
{
  TFile *output = new TFile(filename,"recreate");

  TTree *tree=new TTree("tree","tree");

  double x,y;

  tree->Branch("x",&x,"x/D");
  tree->Branch("y",&y,"y/D");
  
  TRandom2 *r = new TRandom2();

  for(int i=0;i<1e6;i++){
    x = 1+r->Rndm()*9;
    y=x*2;
    tree->Fill();
  }

  output->Write();

  output->Close();
}

void chain()
{
  TChain *ch1=new TChain("tree");

  ch1->Add("tut21a.root");
  ch1->Add("tut21b.root");
  ch1->Add("tut21b.root");
  
  double x;

  ch1->SetBranchAddress("x",&x);

  int entries = ch1->GetEntries();

  TH1F *hist = new TH1F("hist","Histogram",100,1,10);


  for(int i=0;i<entries;i++){
    ch1->GetEntry(i);
    hist->Fill(x);
  }

  TCanvas *c1=new TCanvas();
  hist->Draw();
}



void tut21()
{
  write("tut21a.root");
  write("tut21b.root");

  chain();
}
