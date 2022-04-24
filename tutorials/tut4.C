void tut4(){
    //classTGraph


    TGraph *gr = new TGraph();

    //gr->SetMarkerStyle(4);
    //gr->SetMarkerStyle(kCircle);
    gr->SetMarkerStyle(kFullCircle);
    gr->SetLineWidth(2);
    gr->SetLineColor(kRed);

    gr->SetTitle("Graph");
    gr->GetXaxis()->SetTitle("X Values");
    gr->GetYaxis()->SetTitle("Y Values");

    //  open and read a file

    fstream file;
    file.open("data2.txt",ios::in);

    while(1)
    {
        double x,y;
        file >> x >> y;
        gr->SetPoint(gr->GetN(),x,y);
        if(file.eof()) break;
    }

    file.close();

    //

    
    TCanvas *c1 = new TCanvas();
    //gr -> Draw("AL");
    //gr -> Draw("AL*");
    //gr -> Draw("ALP");
    gr -> Draw("ACP");
    //A means graph,L line ,C curve ,P points.
}