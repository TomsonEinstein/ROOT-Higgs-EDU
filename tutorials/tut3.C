void tut3(){

    //file data.txt
    //file data_casio.txt

    
    //TH1F *hist = new TH1F("hist","Histogram",6,1,7);
    TH1F *hist = new TH1F("hist","Histogram",15,1,11);
    //root.cern.ch/doc/master/classTH1F.html

    fstream file;
    //file.open("data.txt",ios::in);
    file.open("data_casio.txt",ios::in);

    double value;

    while (1)
    {
        file >> value ;
        hist ->Fill(value);
        if(file.eof()) break;
    }
    

    hist->GetXaxis()->SetTitle("Grade");
    hist->GetYaxis()->SetTitle("Entries");
    

    TCanvas *c1 = new TCanvas();
    hist->Draw();
}