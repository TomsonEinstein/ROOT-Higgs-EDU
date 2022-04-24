void tut16()
{ 
  TCanvas *c1=new TCanvas();

  TFile *input = new TFile("data4.root","read");

  TTree *tree =(TTree*)input->Get("tree");

  TH1F *hist = new TH1F("hist","Histogram",20,0,20);

  

  double x,y;
  
  int entries =tree->GetEntries();
  cout << entries << endl;
  tree->SetBranchAddress("x",&x);
  tree->SetBranchAddress("y",&y);

  for(int i = 0;i<entries;i++)
  {
    tree->GetEntry(i);

    cout << x << " " << y << endl;

    hist->Fill(x);
  }
  hist->Draw();

  //input->Close();  


}
