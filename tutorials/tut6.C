void tut6(){
    TH1F *hist = new TH1F("hist","Histogram",100,0,10);
    //root.cern.ch/doc/master/classTH1F.html

    fstream file;
    file.open("data1.txt",ios::out);

    TRandom2 *rand = new TRandom2(3);


    for (int i = 0; i < 1000; i++)
    {
        double r = rand->Gaus(5,1);
        file << r << endl;
    }
    file.close();
    file.open("data1.txt",ios::in);

    double value;

    while (1)
    {
        file >> value ;
        hist ->Fill(value);
        if(file.eof()) break;
    }
    

    hist->GetXaxis()->SetTitle("Distribution");
    hist->GetYaxis()->SetTitle("Entries");
    

    TCanvas *c1 = new TCanvas();
    hist->Draw();
}