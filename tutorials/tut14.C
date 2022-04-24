void tut14(){
    //We don't want to draw immediately.We want to store the file if the time to run the code is long.
    TFile *file=new TFile("output.root","RECREATE");
    
    TH1F *hist = new TH1F("hist","Histogram",100,0,100);
    
    hist->Fill(10);
    hist->Fill(90);
    
    //hist->Draw();
    file->Write();

    file->Close();
}
// type new TBrowser in powershell