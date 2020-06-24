package com.company;
import java.io.File;
import java.io.IOException;

public class Main {
    //Caricamento DLL contenente le funzioni c definite nel file header com_company_MetodiNativi.h tramite il percorso assoluto del file
    static {
        String directory = null;
        try {
            directory = new File(".").getCanonicalPath();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.load(directory+"\\src\\com\\company\\MasterC.dll");
    }

    public static void main(String[] args) {
	    Mastermind m=new Mastermind();
	    m.StartMastermind();
    }
    //Nota la classe MetodiNativi e' stata utilizzata esclusivamente per la definizione dei metodi nativi e la creazione del file header
}
