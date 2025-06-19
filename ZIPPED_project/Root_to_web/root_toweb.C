{
    // New ROOT SESSION

    TCanvas *c500 = new TCanvas("c500", "Drawing to the WEB", 10, 10, 600, 600);

    char *fnames[50]; //  we could have 50 images, this takes little space
    for (int k = 0; k < 50; k++)
        fnames[k] = new char[14];
    for (int k = 0; k < 50; k++)
        sprintf(fnames[k], "pict%d.png", k);

    FILE *outfil;
    outfil = fopen("index.html", "w");
    fprintf(outfil, "<html>\n"); //    starting HTML
    fprintf(outfil, "<head>\n");
    fprintf(outfil, "<title>\n");
    fprintf(outfil, "The title - ROOT to WEB");
    fprintf(outfil, "</title>\n");
    fprintf(outfil, "</head>\n");
    fprintf(outfil, "<body style="); //  specify the font and colors

    fprintf(outfil, "\"font-family:monospace; font-size: 16pt; ");
    fprintf(outfil, " color:#0000AA; background-color:#FFFFAA\"> \n");

    //    To printf "  inside of "   "   you use    \"
    //       printf(" \"  \" --")    prints   "  " --

    int I = 0;
    TF1 *func;
    TString FUNC;

    //  LOOP BY HAND
    FUNC = "cos(2*x)*exp(-0.3*x)";
    func = new TF1("func", FUNC, 0, 10);
    func->Draw();
    fprintf(outfil, "<hr><br>This image: function  %s \n<br>\n", FUNC.Data());
    fprintf(outfil, "       ");
    fprintf(outfil, " <img src=\"%s\"><br>\n", fnames[I]);
    c500->Print(fnames[I]);
    I = I + 1;

    FUNC = "sin(4*x)*exp(-0.5*x)";
    func = new TF1("func", FUNC, 0, 10);
    func->Draw();
    fprintf(outfil, "<hr><br>This image: function  %s \n<br>\n", FUNC.Data());
    fprintf(outfil, "<img src=\"%s\"><br>\n", fnames[I]);
    c500->Print(fnames[I]);
    I = I + 1;

    FUNC = "cos(2*x)*exp(0.3*x)";
    func = new TF1("func", FUNC, 0, 10);
    func->Draw();
    fprintf(outfil, "<hr><br>This image: function  %s \n<br>\n", FUNC.Data());
    fprintf(outfil, "       ");
    fprintf(outfil, "       ");
    fprintf(outfil, " <img src=\"%s\"><br>\n", fnames[I]);
    c500->Print(fnames[I]);
    I = I + 1;

    //  fprintf(outfil,"</body>\n");     // should be there
    //  fprintf(outfil,"</html>\n");      // but browsers are forgiving

    fclose(outfil);
    system("txtbox_blue index.html");
    system("cat index.html.html >> index.html");
    system("txtbox_white root_to_webN.C");
    system("cat root_to_webN.C.html >> index.html");
}