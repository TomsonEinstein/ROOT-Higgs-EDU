void tut9(){
    TH1F *hist = new TH1F("hist","Histogram",100,0,15);
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
    hist->SetFillColor(kGreen-9);
    hist->GetXaxis()->SetTitle("Distribution");
    hist->GetYaxis()->SetTitle("Entries");

    hist->GetXaxis()->SetTitleSize(0.05);
    hist->GetYaxis()->SetTitleSize(0.05);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetXaxis()->SetLabelSize(0.05);


    TF1 *fit = new TF1("fit","gaus",0,15);//a new way to fit instead of using Fit

    fit->SetLineWidth(3);
    //fit->SetLineColor(kBlue);
    fit->SetLineStyle(2);
    
    //If you have problems using fit,you should enter the parameter yourself
    
    fit->SetParameter(0,40);
    fit->SetParameter(1,5);
    fit->SetParameter(2,1);

    //end

    TCanvas *c1 = new TCanvas();
    hist->SetStats(0);//remove the statistic board.
    c1->SetTickx();
    c1->SetTicky();
    c1->SetGridx();
    c1->SetGridy();
    hist->Draw();
    hist->Fit("fit","R");//R,Q,0 for different meanings.

    //Tlegend
    TLegend *leg = new TLegend(0.5,0.6,0.8,0.8);
    leg->SetBorderSize(0);
    leg->AddEntry(hist,"Measured Data","f");//l line ,p points,f filling,and combination.
    leg->AddEntry(fit,"Fit Function","l");
    leg->Draw();


    //watch your parameter

    double mean = fit->GetParameter(1);
    double sigma = fit->GetParameter(2);
    cout << endl;
    cout << mean/sigma << endl;
    
}
