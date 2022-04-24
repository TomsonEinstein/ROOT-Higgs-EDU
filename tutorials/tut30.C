void tut30()
{
	TF1 *f = new TF1("f","[0]*cos([1]*x)",-5,5);
	
	f->SetParameter(0,1);
	f->SetParameter(1,1);
	
	TCanvas *c1 = new TCanvas();
	f->Draw();
	
	ROOT::Math::RootFinder finder;
	finder.Solve(*f,-5,0);
	double solution = finder.Root();
	cout << solution <<endl;
	finder.Solve(*f,0,5);
	double solution2 = finder.Root();
	cout << solution2 <<endl;
	
	TLine *l1 = new TLine(-5,0,5,0);
	TLine *l2 = new TLine(solution,-2.,solution,2);
	TLine *l3 = new TLine(solution2,-2.,solution2,2);
	l1->Draw();
	l2->Draw();
	l3->Draw();
}
