void plot(){
    TFile *file = new TFile("output.root","READ");

    TH1F *hist = (TH1F*)file->Get("hist");

    hist->Draw();

    //file->Close();
}

//use tut14 and plot you can restore the data and create the histogram later.