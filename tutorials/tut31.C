void tut31()
{
	TH1F *hist1 = new TH1F("hist1","Histogram",100,-10,10);
	TH1F *hist2 = new TH1F("hist2","Histogram",100,-10,10);
	
	hist1->FillRandom("gaus");
	hist2->FillRandom("gaus");
	//hist->Scale(1/hist1->GetEntries());
	//hist->Scale(1/hist1->GetMaximum());
	
	TH1F *hist3 = new TH1F();
	
	*hist3 = (*hist1)/(*hist2);
	
	//hist1->Add(hist2);
	//hist1->Add(hist2);
	//hist1->Add(hist2);
	
	TCanvas *c1 = new TCanvas();
	hist3->Draw("hist");
}
