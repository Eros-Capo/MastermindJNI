package com.company;
import java.util.Scanner;

public class Mastermind {
    public static int MAX_TENTATIVI=10;
    Scanner s=new Scanner(System.in);
    private int NuovaPartita=0;

    //Costrutore oggetto Mastermind
    public void Mastermind(){
    }

    //Metodo principale che sfrutta i metodi nativi definiti nella classe MetodiNativi per avviare e svolgere il programma
    public void StartMastermind(){
        int win=0,i;
        int[] codice=null,CodiceUtente=null; //Dichiarazione e istanzazione degli array che riceveranno i codici dai metodi nativi
        codice=MetodiNativi.CreateCode(); //Metodo nativo per la creazione di un array di numeri random che ritorna l'array creato
        //Ciclo for utilizzato per far inserire all'utente 10 volte una combinazione
        for (i=0;i<MAX_TENTATIVI;i++){
            //Struttura selettiva if utilizzata per definire se l'utente ha vinto o no
            if (win==0) {
                CodiceUtente=MetodiNativi.UserInput(); //Metodo nativo utilizzato per ricevere in input la combinazione scelta dall'utente (Restituisce la combinazione in un array)
                win = MetodiNativi.Controllo(codice, CodiceUtente); //Metodo nativo utilizzato per testare la combinazione scelta dall'utente (Restituisce 0 in caso di sconfitta o 1 in caso di vittoria)
            }else if (win==1){
                System.out.print("Il codice era: ");
                for (i=0;i<4;i++){
                    System.out.print(codice[i]);
                }
                System.out.println(" Complimenti hai vinto! Inserisci 1 per giocare di nuovo o 0 per uscire");
                NuovaPartita=s.nextInt();
                newGame(NuovaPartita); //Metodo ricorsivo utilizzato per richiamare la funzione StartMastermind ed iniziare una nuova partita
            }
        }
        //Ciclo if utilizzato per comunicare la sconfitta all'utente in caso di terminazione dei tentativi
        if (win==0 && i==MAX_TENTATIVI) {
            System.out.println("Hai perso! Inserisci 1 per giocare di nuovo o 0 per uscire");
            NuovaPartita = s.nextInt();
            newGame(NuovaPartita);
        }
    }

    //Metodo utilizzato per richiamare la funzione StartMastermind
    public void newGame(int x){
        if(x==1){
            StartMastermind();
        }else if (x==0){
            System.exit(0);
        }
    }
}