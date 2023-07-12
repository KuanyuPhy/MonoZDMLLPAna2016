void for_signalflavor_jet(int flavor, float hadronflavor, float tmp, float Weight, TH1F *h_tmp)
{
    if (hadronflavor == flavor)
    {
        h_tmp->Fill(tmp, Weight);
    }
}
void for_doubleflavor_jet(int flavor1, float flavor2, float hadronflavor, float tmp, float Weight, TH1F *h_tmp)
{
    if (hadronflavor == flavor1 || hadronflavor == flavor2)
    {
        h_tmp->Fill(tmp, Weight);
    }
}