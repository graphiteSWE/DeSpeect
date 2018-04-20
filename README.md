# Despeect-ProductBaseline

[![Build Status](https://travis-ci.org/graphiteSWE/Despeect-ProductBaseline.svg?branch=master)](https://travis-ci.org/graphiteSWE/Despeect-ProductBaseline)
[![BCH compliance](https://bettercodehub.com/edge/badge/graphiteSWE/Despeect-ProductBaseline?branch=master)](https://bettercodehub.com/)

## Introduzione

Product Baseline del gruppo Graphite per il progetto DeSpeect, realizzato in collaborazione con Mivoq s.r.l. per il progetto didattico del corso di Ingegneria del Software del cdl in Informatica dell'Università degli Studi di Padova.

### Riferimenti informativi

* [Documentazione Speect](http://speect.sourceforge.net/ "Documentazione Speect")
* [Documentazione Qt](http://doc.qt.io/ "Documentazione Qt")
* [Speect di Mivoq s.r.l.](https://github.com/mivoq/speect "Mivoq Speect") 


## Tecnologie impiegate

* Qt 5.9 LTS
* CMAKE 2.8
* Speect 1.1.0-69-g65f4
* Ubuntu 16.04 LTS
* Travis CI

## Prerequisiti

* Sistema operativo Unix / Unix-like (il software è stato testato solo per piattaforma Ubuntu 16.04 LTS)
* CMAKE (versione minima 2.8)
* Compilatore ANSI C/ISO C90 GCC (versione minima 5.0)
* Qt 5.9.0

## Installazione ed esecuzione

Per installare ed eseguire, attenersi alla seguente procedura:

1. Clonare o scaricare la repository sulla propria macchina
2. Eseguire lo script `build.sh`
3. Entrare nella cartella della build con il comando `cd DeSpeect/build/`
4. Avviare l'eseguibile con il comando `./main`

## Stampare un grafo

Per stampare un grafo è sufficiente caricare un file `.json` corrispondente a una voice cliccando sul pulsante `Load Voice` in alto a sinistra nella GUI, e successivamente avviare la stampa. Le voice disponibili sono contenute nella directory `SpeectInstaller/voices/`. Segue un esempio di procedura d'esecuzione:

1. Aprire l'interfaccia grafica
2. Cliccare il pulsante `Load Voice`
3. Aprire il file corrispondente al path `SpeectInstaller/voices/cmu_arctic_slt/voice.json`
4. Selezionare gli utterance processor desiderati dall'omonima barra laterale
5. Cliccare il pulsante `Run step` per eseguire gli utterance processor uno alla volta, oppure `Run all` per eseguirli tutti di seguito
