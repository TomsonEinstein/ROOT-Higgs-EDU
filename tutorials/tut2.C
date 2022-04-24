void tut2(){
    //classTGraph
    double x[5] = {1,2,3,4,5};
    double y[5] = {1,4,9,16,25};

    TGraph *gr = new TGraph(5, x , y );

    //gr->SetMarkerStyle(4);
    //gr->SetMarkerStyle(kCircle);
    gr->SetMarkerStyle(kFullCircle);
    gr->SetMarkerSize(5);

    TCanvas *c1 = new TCanvas();
    //gr -> Draw("AL");
    //gr -> Draw("AL*");
    //gr -> Draw("ALP");
    gr -> Draw("ACP");
    //A means graph,L line ,C curve ,P points.
}