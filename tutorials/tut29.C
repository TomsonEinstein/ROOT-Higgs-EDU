void tut29()
{
	TCanvas *c1 = new TCanvas();
	
	TH1F *hist = new TH1F("hist","Histogram",100,-5,5);
	
	gSystem->Unlink("tut29.gif");
	
	TRandom *r1 = new TRandom();
	
	for(int i = 0 ; i < 1e3;i++)
	{
		double val = r1->Gaus();
		hist->Fill(val);
		c1->Update();
		if(i%100 == 0)
		{
			hist->Draw();
			hist->Fit("gaus");
			c1->Modified();
			c1->Print("tut29.gif+");
		}
		//sleep(1);
	}
}
