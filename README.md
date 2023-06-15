# LED Lampbesturing met Firebase

Dit project demonstreert hoe je LED-lampen kunt besturen met behulp van Firebase Realtime Database. Het maakt gebruik van een ESP32-board en de Firebase ESP Client-bibliotheek om een verbinding met Firebase tot stand te brengen en de LED-waarden in realtime bij te werken.

## Werking van de code

De code begint met het importeren van de vereiste bibliotheken, waaronder WiFi.h en Firebase_ESP_Client.h. Vervolgens worden de pinnummers voor de LED's, netwerkreferenties en Firebase-projectgegevens gedefinieerd.

In de `setup()`-functie wordt de seriële communicatie gestart, de LED-pinnen geconfigureerd en verbinding gemaakt met het WiFi-netwerk. Vervolgens wordt er aangemeld bij Firebase met de opgegeven API-sleutel. Als de aanmelding succesvol is, wordt het vlaggenvariabele `signupOK` ingesteld op `true`. De Firebase-configuratie en authenticatiegegevens worden ingesteld en de initiële LED-waarden worden in Firebase geplaatst.

De `loop()`-functie wordt continu uitgevoerd. Als Firebase gereed is, er succesvol is aangemeld en er 2 seconden zijn verstreken sinds de laatste gegevensverzending, worden de LED-waarden gewijzigd. De LED's worden in- of uitgeschakeld op basis van de waarde van `ledValue1` en `ledValue2`. Vervolgens worden de nieuwe LED-waarden naar Firebase verzonden. De status van de LED-updates wordt weergegeven in de seriële monitor.

![](include/ESP-32 POC.gif)

## Installatie

1. Open de Arduino IDE.
2. Installeer de vereiste bibliotheken:
   - WiFi.h
   - Firebase_ESP_Client.h
3. Maak een nieuw Arduino-sketch-bestand en kopieer de code erin.
4. Werk de volgende variabelen bij met je netwerkreferenties en de gegevens van je Firebase-project:
   - `WIFI_SSID`: De naam (SSID) van je WiFi-netwerk.
   - `WIFI_PASSWORD`: Het wachtwoord van je WiFi-netwerk.
   - `API_KEY`: De API-sleutel van je Firebase-project.
   - `DATABASE_URL`: De URL van je Firebase Realtime Database.
5. Sluit het ESP32-board aan op je computer.
6. Selecteer het juiste board en de juiste poort in het menu 'Hulpmiddelen' van de Arduino IDE.
7. Upload het sketch-bestand naar het ESP32-board.

## Gebruik

1. Open de seriële monitor in de Arduino IDE.
2. Het ESP32-board zal proberen verbinding te maken met het opgegeven WiFi-netwerk. De seriële monitor toont de verbindingsstatus en het toegewezen IP-adres.
3. Als de verbinding succesvol is, meldt het board zich aan bij Firebase met de opgegeven API-sleutel. De seriële monitor toont "ok" als de aanmelding succesvol is, anders wordt er een foutmelding weergegeven.
4. Het board initialiseert de LED-waarden in de Firebase Realtime Database.
5. De `loop`-functie schakelt continu de LED-waarden om de 2 seconden en werkt de Firebase-database dien

overeenkomstig bij.
6. De seriële monitor toont de status van de LED-updates in Firebase.

## Schakelschema

Deze code gaat ervan uit dat de LED's zijn aangesloten op pin 13 en 12 van het ESP32-board. Je kunt de pinnummers in de code aanpassen als je de LED's op andere pinnen hebt aangesloten.

```
    ESP32        LED
    ------      ------
    Pin 13 <--> LED A
    Pin 12 <--> LED B
```

## Probleemoplossing

- Als je problemen ondervindt, controleer dan of je de vereiste bibliotheken correct hebt geïnstalleerd.
- Controleer je netwerkreferenties voor WiFi en zorg ervoor dat het ESP32-board binnen het bereik van de WiFi-router ligt.
- Controleer of je de API-sleutel en URL van de Firebase Realtime Database correct hebt ingevoerd.
- Controleer de seriële uitvoer op eventuele foutmeldingen of verbindingsproblemen.
