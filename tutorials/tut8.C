void tut8(){
    TH1F *hist = new TH1F("hist","Histogram",100,0,10);
    //root.cern.ch/doc/master/classTH1F.html

    //create the file

    fstream file;
    file.open("data1.txt",ios::out);

    TRandom2 *rand = new TRandom2(3);


    for (int i = 0; i < 1000; i++)
    {
        double r = rand->Gaus(5,1);
        file << r << endl;
    }
    file.close();
    
    //read the file
    
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
    
    TF1 *fit = new TF1("fit","gaus",0,10);//a new way to fit instead of using Fit
    
    //If you have problems using fit,you should enter the parameter yourself
    
    fit->SetParameter(0,40);
    fit->SetParameter(1,5);
    fit->SetParameter(2,1);

    //end

    TCanvas *c1 = new TCanvas();
    hist->SetStats(0);//remove the statistic board.
    hist->Draw();
    hist->Fit("fit","R");//R,Q,0 for different meanings.

    //Tlegend
    TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
    leg->AddEntry(hist,"Measured Data","l");//l line ,p points,f filling,and combination.
    leg->AddEntry(fit,"Fit Function","l");
    leg->Draw();


    //watch your parameter

    double mean = fit->GetParameter(1);
    double sigma = fit->GetParameter(2);
    cout << endl;
    cout << mean/sigma << endl;
    
}