//The following example functions contains examples in Root Primer Letter and Root User Guide.
//There are also some functions written by myself.
//All of these functions are used for studying and improving skills of using Root.

//Official Website https://root.cern.ch/














/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

//My functions


void draw1(){
    //The function is used to create a function plot.
int a,b;
auto efunc=new TF1("efunc","exp([0]+[1]*x)",0.,10.);
cout << "exp([0]+[1]*x)" << endl;
cout << "input variable [0]" << endl;
cin >> a;
cout << "input variable [1]" << endl;
cin >> b;
efunc->SetParameter(0,a);
efunc->SetParameter(1,b);
efunc->Draw();
}

/*******************************************************************************************/

void histogram1(){
    //The function is used to create a histogram.
auto h1 = new TH1F("h1","Histo from a Gaussian",100,-3,3);
h1->FillRandom("gaus",10000);
h1->Draw();
//auto h2 = new TH1F("h2","Histo from existing histo",100,-3,3);
//h2->FillRandom((TH1F*)&h1, 100);
//h2->Draw();
}

/*******************************************************************************************/

void getrandomh() {
    //The function is used to create two random histograms.
   TH1F *source = new TH1F("source","source hist",100,-3,3);
   source->FillRandom("gaus",100);
   TH1F *final = new TH1F("final","final hist",100,-3,3);

             // continued...

   for (Int_t i=0;i<10000;i++) {
      final->Fill(source->GetRandom());
   }
   TCanvas *c1 = new TCanvas("c1","c1",800,1000);
   c1->Divide(1,2);
   c1->cd(1);
   source->Draw();
   c1->cd(2);
   final->Draw();
   c1->cd();
}

/*******************************************************************************************/














/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

//Example functions in Root Primer Letter

/*******************************************************************************************/
    // slits.C
// Example drawing the interference pattern of light
// falling on a grid with n slits and ratio r of slit
// width over distance between slits.

auto pi = TMath::Pi();

// function code in C
double single(double *x, double *par) {
  return pow(sin(pi*par[0]*x[0])/(pi*par[0]*x[0]),2);
}

double nslit0(double *x,double *par){
  return pow(sin(pi*par[1]*x[0])/sin(pi*x[0]),2);
}

double nslit(double *x, double *par){
  return single(x,par) * nslit0(x,par);
}

// This is the main program
void slits() {
  float r,ns;

  // request user input
  cout << "slit width / g ? ";
  scanf("%f",&r);
  cout << "# of slits? ";
  scanf("%f",&ns);
  cout <<"interference pattern for "<< ns
       <<" slits, width/distance: "<<r<<endl;

  // define function and set options
  TF1 *Fnslit  = new TF1("Fnslit",nslit,-5.001,5.,2);
  Fnslit->SetNpx(500);

  // set parameters, as read in above
  Fnslit->SetParameter(0,r);
  Fnslit->SetParameter(1,ns);

  // draw the interference pattern for a grid with n slits
  Fnslit->Draw();
}

/*******************************************************************************************/

    // macro1.C

// Builds a graph with errors, displays it and saves it as

// image. First, include some header files

// (not necessary for Cling)



#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"

void macro1(){
    // The values and the errors on the Y axis
    const int n_points=10;
    double x_vals[n_points]=
            {1,2,3,4,5,6,7,8,9,10};
    double y_vals[n_points]=
            {6,12,14,20,22,24,35,45,44,53};
    double y_errs[n_points]=
            {5,5,4.7,4.5,4.2,5.1,2.9,4.1,4.8,5.43};

    // Instance of the graph
    TGraphErrors graph(n_points,x_vals,y_vals,nullptr,y_errs);
    graph.SetTitle("Measurement XYZ;lenght [cm];Arb.Units");

    // Make the plot estetically better
    graph.SetMarkerStyle(kOpenCircle);
    graph.SetMarkerColor(kBlue);
    graph.SetLineColor(kBlue);

    // The canvas on which we'll draw the graph
    auto  mycanvas = new TCanvas();

    // Draw the graph !
    graph.DrawClone("APE");

    // Define a linear function
    TF1 f("Linear law","[0]+x*[1]",.5,10.5);
    // Let's make the function line nicer
    f.SetLineColor(kRed); f.SetLineStyle(2);
    // Fit it to the graph and draw it
    graph.Fit(&f);
    f.DrawClone("Same");

    // Build and Draw a legend
    TLegend leg(.1,.7,.3,.9,"Lab. Lesson 1");
    leg.SetFillColor(0);
    graph.SetFillColor(0);
    leg.AddEntry(&graph,"Exp. Points");
    leg.AddEntry(&f,"Th. Law");
    leg.DrawClone("Same");

    // Draw an arrow on the canvas
    TArrow arrow(8,8,6.2,23,0.02,"|>");
    arrow.SetLineWidth(2);
    arrow.DrawClone();

    // Add some text to the plot
    TLatex text(8.2,7.5,"#splitline{Maximum}{Deviation}");
    text.DrawClone();

    mycanvas->Print("graph_with_law.pdf");
}

int main(){
    macro1();
    }
/*******************************************************************************************/

    //macro2.C

// Reads the points from a file and produces a simple graph.

int macro2(){
    auto c=new TCanvas();c->SetGrid();
    
    TGraphErrors graph_expected("./macro2_input_expected.txt",
                                "%lg %lg %lg");
    graph_expected.SetTitle(
       "Measurement XYZ and Expectation;"
       "lenght [cm];"
       "Arb.Units");
    graph_expected.SetFillColor(kYellow);
    graph_expected.DrawClone("E3AL"); // E3 draws the band

    TGraphErrors graph("./macro2_input.txt","%lg %lg %lg");
    graph.SetMarkerStyle(kCircle);
    graph.SetFillColor(0);
    graph.DrawClone("PESame");

    // Draw the Legend
    TLegend leg(.1,.7,.3,.9,"Lab. Lesson 2");
    leg.SetFillColor(0);
    leg.AddEntry(&graph_expected,"Expected Points");
    leg.AddEntry(&graph,"Measured Points");
    leg.DrawClone("Same");

    graph.Print();
    return 0;
}
/*******************************************************************************************/

    //macro3.C

// Builds a polar graph in a square Canvas.

void macro3(){
    auto c = new TCanvas("myCanvas","myCanvas",600,600);
    double rmin = 0.;
    double rmax = TMath::Pi()*6.;
    const int npoints = 1000;
    double r[npoints];
    double theta[npoints];
    for (int ipt = 0; ipt < npoints; ipt++) {
        theta[ipt] = ipt*(rmax-rmin)/npoints+rmin;
        r[ipt] = TMath::Sin(theta[ipt]);
    }
    auto grP1 = new TGraphPolar(npoints,theta,r);
    grP1->SetTitle("A Fan");
    grP1->SetLineWidth(3);
    grP1->SetLineColor(2);
    grP1->Draw("L");
    gPad->Update();
    grP1->GetPolargram()->SetToRadian();
}


/*******************************************************************************************/

    //macro4.C

// Create, Draw and fit a TGraph2DErrors
void macro4(){
   gStyle->SetPalette(kBird);
   const double e = 0.3;
   const int nd = 500;

   TRandom3 my_random_generator;
   TF2 f2("f2",
          "1000*(([0]*sin(x)/x)*([1]*sin(y)/y))+200",
          -6,6,-6,6);
   f2.SetParameters(1,1);
   TGraph2DErrors dte(nd);
   // Fill the 2D graph
   double rnd, x, y, z, ex, ey, ez;
   for (Int_t i=0; i<nd; i++) {
      f2.GetRandom2(x,y);
      // A random number in [-e,e]
      rnd = my_random_generator.Uniform(-e,e);
      z = f2.Eval(x,y)*(1+rnd);
      dte.SetPoint(i,x,y,z);
      ex = 0.05*my_random_generator.Uniform();
      ey = 0.05*my_random_generator.Uniform();
      ez = fabs(z*rnd);
      dte.SetPointError(i,ex,ey,ez);
   }
   // Fit function to generated data
   f2.SetParameters(0.7,1.5);  // set initial values for fit
   f2.SetTitle("Fitted 2D function");
   dte.Fit(&f2);
   // Plot the result
   auto c1 = new TCanvas();
   f2.SetLineWidth(1);
   f2.SetLineColor(kBlue-5);
   TF2   *f2c = (TF2*)f2.DrawClone("Surf1");
   TAxis *Xaxis = f2c->GetXaxis();
   TAxis *Yaxis = f2c->GetYaxis();
   TAxis *Zaxis = f2c->GetZaxis();
   Xaxis->SetTitle("X Title"); Xaxis->SetTitleOffset(1.5);
   Yaxis->SetTitle("Y Title"); Yaxis->SetTitleOffset(1.5);
   Zaxis->SetTitle("Z Title"); Zaxis->SetTitleOffset(1.5);
   dte.DrawClone("P0 Same");
   // Make the x and y projections
   auto c_p= new TCanvas("ProjCan",
                         "The Projections",1000,400);
   c_p->Divide(2,1);
   c_p->cd(1);
   dte.Project("x")->Draw();
   c_p->cd(2);
   dte.Project("y")->Draw();
}

/*******************************************************************************************/

    //multigraph.C

// Manage several graphs as a single entity.
void multigraph(){
   TCanvas *c1 = new TCanvas("c1","multigraph",700,500);
   c1->SetGrid();

   TMultiGraph *mg = new TMultiGraph();

   // create first graph
   const Int_t n1 = 10;
   Double_t px1[] = {-0.1, 0.05, 0.25, 0.35, 0.5, 0.61,0.7,0.85,0.89,0.95};
   Double_t py1[] = {-1,2.9,5.6,7.4,9,9.6,8.7,6.3,4.5,1};
   Double_t ex1[] = {.05,.1,.07,.07,.04,.05,.06,.07,.08,.05};
   Double_t ey1[] = {.8,.7,.6,.5,.4,.4,.5,.6,.7,.8};
   TGraphErrors *gr1 = new TGraphErrors(n1,px1,py1,ex1,ey1);
   gr1->SetMarkerColor(kBlue);
   gr1->SetMarkerStyle(21);
   mg->Add(gr1);

   // create second graph
   const Int_t n2 = 10;
   Float_t x2[]  = {-0.28, 0.005, 0.19, 0.29, 0.45, 0.56,0.65,0.80,0.90,1.01};
   Float_t y2[]  = {2.1,3.86,7,9,10,10.55,9.64,7.26,5.42,2};
   Float_t ex2[] = {.04,.12,.08,.06,.05,.04,.07,.06,.08,.04};
   Float_t ey2[] = {.6,.8,.7,.4,.3,.3,.4,.5,.6,.7};
   TGraphErrors *gr2 = new TGraphErrors(n2,x2,y2,ex2,ey2);
   gr2->SetMarkerColor(kRed);
   gr2->SetMarkerStyle(20);
   mg->Add(gr2);

   mg->Draw("apl");
   mg->GetXaxis()->SetTitle("X values");
   mg->GetYaxis()->SetTitle("Y values");

   gPad->Update();
   gPad->Modified();
}

/*******************************************************************************************/

    //macro5.C

// Create, Fill and draw an Histogram which reproduces the
// counts of a scaler linked to a Geiger counter.

void macro5(){
    auto cnt_r_h=new TH1F("count_rate",
                "Count Rate;N_{Counts};# occurencies",
                100, // Number of Bins
                -0.5, // Lower X Boundary
                15.5); // Upper X Boundary

    auto mean_count=3.6f;
    TRandom3 rndgen;
    // simulate the measurements
    for (int imeas=0;imeas<400;imeas++)
        cnt_r_h->Fill(rndgen.Poisson(mean_count));

    auto c= new TCanvas();
    cnt_r_h->Draw();

    auto c_norm= new TCanvas();
    cnt_r_h->DrawNormalized();

    // Print summary
    cout << "Moments of Distribution:\n"
         << " - Mean     = " << cnt_r_h->GetMean() << " +- "
                             << cnt_r_h->GetMeanError() << "\n"
         << " - Std Dev  = " << cnt_r_h->GetStdDev() << " +- "
                             << cnt_r_h->GetStdDevError() << "\n"
         << " - Skewness = " << cnt_r_h->GetSkewness() << "\n"
         << " - Kurtosis = " << cnt_r_h->GetKurtosis() << "\n";
}

/*******************************************************************************************/

    //  macro6.C

// Divide and add 1D Histograms

void format_h(TH1F* h, int linecolor){
    h->SetLineWidth(3);
    h->SetLineColor(linecolor);
    }

void macro6(){

    auto sig_h=new TH1F("sig_h","Signal Histo",50,0,10);
    auto gaus_h1=new TH1F("gaus_h1","Gauss Histo 1",30,0,10);
    auto gaus_h2=new TH1F("gaus_h2","Gauss Histo 2",30,0,10);
    auto bkg_h=new TH1F("exp_h","Exponential Histo",50,0,10);

    // simulate the measurements
    TRandom3 rndgen;
    for (int imeas=0;imeas<4000;imeas++){
        bkg_h->Fill(rndgen.Exp(4));
        if (imeas%4==0) gaus_h1->Fill(rndgen.Gaus(5,2));
        if (imeas%4==0) gaus_h2->Fill(rndgen.Gaus(5,2));
        if (imeas%10==0)sig_h->Fill(rndgen.Gaus(5,.5));}

    // Format Histograms
    int i=0;
    for (auto hist : {sig_h,bkg_h,gaus_h1,gaus_h2})
        format_h(hist,1+i++);

    // Sum
    auto sum_h= new TH1F(*bkg_h);
    sum_h->Add(sig_h,1.);
    sum_h->SetTitle("Exponential + Gaussian;X variable;Y variable");
    format_h(sum_h,kBlue);

    auto c_sum= new TCanvas();
    sum_h->Draw("hist");
    bkg_h->Draw("SameHist");
    sig_h->Draw("SameHist");

    // Divide
    auto dividend=new TH1F(*gaus_h1);
    dividend->Divide(gaus_h2);

    // Graphical Maquillage
    dividend->SetTitle(";X axis;Gaus Histo 1 / Gaus Histo 2");
    format_h(dividend,kOrange);
    gaus_h1->SetTitle(";;Gaus Histo 1 and Gaus Histo 2");
    gStyle->SetOptStat(0);

    TCanvas* c_divide= new TCanvas();
    c_divide->Divide(1,2,0,0);
    c_divide->cd(1);
    c_divide->GetPad(1)->SetRightMargin(.01);
    gaus_h1->DrawNormalized("Hist");
    gaus_h2->DrawNormalized("HistSame");

    c_divide->cd(2);
    dividend->GetYaxis()->SetRangeUser(0,2.49);
    c_divide->GetPad(2)->SetGridy();
    c_divide->GetPad(2)->SetRightMargin(.01);
    dividend->Draw();
}

/*******************************************************************************************/

    //  macro7.C

// Draw a Bidimensional Histogram in many ways
// together with its profiles and projections

void macro7(){
   gStyle->SetPalette(kBird);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);

   auto bidi_h = new TH2F("bidi_h","2D Histo;Gaussian Vals;Exp. Vals",
                          30,-5,5,  // X axis
                          30,0,10); // Y axis

   TRandom3 rgen;
   for (int i=0;i<500000;i++) {
      bidi_h->Fill(rgen.Gaus(0,2),10-rgen.Exp(4),.1);
   }

   auto c=new TCanvas("Canvas","Canvas",800,800);
   c->Divide(2,2);
   c->cd(1); bidi_h->Draw("Cont1");
   c->cd(2); bidi_h->Draw("Colz");
   c->cd(3); bidi_h->Draw("Lego2");
   c->cd(4); bidi_h->Draw("Surf3");

   // Profiles and Projections
   auto c2=new TCanvas("Canvas2","Canvas2",800,800);
   c2->Divide(2,2);
   c2->cd(1); bidi_h->ProjectionX()->Draw();
   c2->cd(2); bidi_h->ProjectionY()->Draw();
   c2->cd(3); bidi_h->ProfileX()->Draw();
   c2->cd(4); bidi_h->ProfileY()->Draw();
}

/*******************************************************************************************/

    //  hstack.C

// Example of stacked histograms using the class THStack

void hstack(){
   THStack *a = new THStack("a","Stacked 2D histograms");

   TF2 *f1 = new TF2("f1","xygaus + xygaus(5) + xylandau(10)",-4,4,-4,4);
   Double_t params1[] = {130,-1.4,1.8,1.5,1, 150,2,0.5,-2,0.5, 3600,-2,0.7,-3,0.3};
   f1->SetParameters(params1);
   TH2F *h2sta = new TH2F("h2sta","h2sta",20,-4,4,20,-4,4);
   h2sta->SetFillColor(38);
   h2sta->FillRandom("f1",4000);

   TF2 *f2 = new TF2("f2","xygaus + xygaus(5)",-4,4,-4,4);
   Double_t params2[] = {100,-1.4,1.9,1.1,2, 80,2,0.7,-2,0.5};
   f2->SetParameters(params2);
   TH2F *h2stb = new TH2F("h2stb","h2stb",20,-4,4,20,-4,4);
   h2stb->SetFillColor(46);
   h2stb->FillRandom("f2",3000);

   a->Add(h2sta);
   a->Add(h2stb);

   a->Draw();
}

/*******************************************************************************************/

    //  macro8.C

void format_line(TAttLine* line,int col,int sty){
    line->SetLineWidth(5); line->SetLineColor(col);
    line->SetLineStyle(sty);}

double the_gausppar(double* vars, double* pars){
    return pars[0]*TMath::Gaus(vars[0],pars[1],pars[2])+
        pars[3]+pars[4]*vars[0]+pars[5]*vars[0]*vars[0];}

int macro8(){
    gStyle->SetOptTitle(0); gStyle->SetOptStat(0);
    gStyle->SetOptFit(1111); gStyle->SetStatBorderSize(0);
    gStyle->SetStatX(.89); gStyle->SetStatY(.89);

    TF1 parabola("parabola","[0]+[1]*x+[2]*x**2",0,20);
    format_line(&parabola,kBlue,2);

    TF1 gaussian("gaussian","[0]*TMath::Gaus(x,[1],[2])",0,20);
    format_line(&gaussian,kRed,2);

    TF1 gausppar("gausppar",the_gausppar,-0,20,6);
    double a=15; double b=-1.2; double c=.03;
    double norm=4; double mean=7; double sigma=1;
    gausppar.SetParameters(norm,mean,sigma,a,b,c);
    gausppar.SetParNames("Norm","Mean","Sigma","a","b","c");
    format_line(&gausppar,kBlue,1);

    TH1F histo("histo","Signal plus background;X vals;Y Vals",50,0,20);
    histo.SetMarkerStyle(8);

    // Fake the data
    for (int i=1;i<=5000;++i) histo.Fill(gausppar.GetRandom());

    // Reset the parameters before the fit and set
    // by eye a peak at 6 with an area of more or less 50
    gausppar.SetParameter(0,50);
    gausppar.SetParameter(1,6);
    int npar=gausppar.GetNpar();
    for (int ipar=2;ipar<npar;++ipar) gausppar.SetParameter(ipar,1);

    // perform fit ...
    auto fitResPtr = histo.Fit(&gausppar, "S");
    // ... and retrieve fit results
    fitResPtr->Print(); // print fit results
    // get covariance Matrix an print it
    TMatrixDSym covMatrix (fitResPtr->GetCovarianceMatrix());
    covMatrix.Print();

    // Set the values of the gaussian and parabola
    for (int ipar=0;ipar<3;ipar++){
        gaussian.SetParameter(ipar,gausppar.GetParameter(ipar));
        parabola.SetParameter(ipar,gausppar.GetParameter(ipar+3));
    }

    histo.GetYaxis()->SetRangeUser(0,250);
    histo.DrawClone("PE");
    parabola.DrawClone("Same"); gaussian.DrawClone("Same");
    TLatex latex(2,220,"#splitline{Signal Peak over}{background}");
    latex.DrawClone("Same");
    return 0;
}

/*******************************************************************************************/

    //  macro9.C

// Toy Monte Carlo example.
// Check pull distribution to compare chi2 and binned
// log-likelihood methods.

void pull( int n_toys = 10000,
      int n_tot_entries = 100,
      int nbins = 40,
      bool do_chi2=true ){

    TString method_prefix("Log-Likelihood ");
    if (do_chi2)
        method_prefix="#chi^{2} ";

    // Create histo
    TH1F h4(method_prefix+"h4",
            method_prefix+" Random Gauss",
            nbins,-4,4);
    h4.SetMarkerStyle(21);
    h4.SetMarkerSize(0.8);
    h4.SetMarkerColor(kRed);

    // Histogram for sigma and pull
    TH1F sigma(method_prefix+"sigma",
               method_prefix+"sigma from gaus fit",
               50,0.5,1.5);
    TH1F pull(method_prefix+"pull",
              method_prefix+"pull from gaus fit",
              50,-4.,4.);

    // Make nice canvases
    auto c0 = new TCanvas(method_prefix+"Gauss",
                          method_prefix+"Gauss",0,0,320,240);
    c0->SetGrid();

    // Make nice canvases
    auto c1 = new TCanvas(method_prefix+"Result",
                          method_prefix+"Sigma-Distribution",
                          0,300,600,400);
    c0->cd();

    float sig, mean;
    for (int i=0; i<n_toys; i++){
     // Reset histo contents
        h4.Reset();
     // Fill histo
        for ( int j = 0; j<n_tot_entries; j++ )
        h4.Fill(gRandom->Gaus());
     // perform fit
        if (do_chi2) h4.Fit("gaus","q"); // Chi2 fit
        else h4.Fit("gaus","lq"); // Likelihood fit
     // some control output on the way
        if (!(i%100)){
            h4.Draw("ep");
            c0->Update();}

     // Get sigma from fit
        TF1 *fit = h4.GetFunction("gaus");
        sig = fit->GetParameter(2);
        mean= fit->GetParameter(1);
        sigma.Fill(sig);
        pull.Fill(mean/sig * sqrt(n_tot_entries));
       } // end of toy MC loop
     // print result
        c1->cd();
        pull.DrawClone();
}

void macro9(){
    int n_toys=10000;
    int n_tot_entries=100;
    int n_bins=40;
    cout << "Performing Pull Experiment with chi2 \n";
    pull(n_toys,n_tot_entries,n_bins,true);
    cout << "Performing Pull Experiment with Log Likelihood\n";
    pull(n_toys,n_tot_entries,n_bins,false);
}

/*******************************************************************************************/

    //  write_to_file.C and read_from_file.C

void write_to_file(){

    // Instance of our histogram
    TH1F h("my_histogram","My Title;X;# of entries",100,-5,5);

    // Let's fill it randomly
    h.FillRandom("gaus");

    // Let's open a TFile
    TFile out_file("my_rootfile.root","RECREATE");

    // Write the histogram in the file
    h.Write();

    // Close the file
    out_file.Close();
}

void read_from_file(){

    // Let's open the TFile
    TFile in_file("my_rootfile.root");

    // Get the Histogram out
    TH1F* h;
    in_file.GetObject("my_histogram",h);

    // Draw it
    auto myCanvas = new TCanvas();
    h->DrawClone();
}
