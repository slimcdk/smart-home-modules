# Ceiling Light Controller

This component fits the general ceiling light socket in Denmark.

### Inputs
M1: Power from switches
M2: Constant power supply
N: Neutral


### Parts list

1x WeMos D1 (ESP8266)
1x WS1228b RGB LED
1x LDR
1x 1/4W 10k Ohms resistor
1x 01x02 Screw terminal (5.08mm pin spacing)
1x 01x03 Screw terminal (5.08mm pin spacing)



-- mains sensing circuit --
1x DB107 Full bridge rectifier
1x LTV-817 Optocoupler
1x 1µf Electrolytic capacitor (min 50V)
1x 1/2W 10k Ohms resistor

-- Power converter --
1x HLK-PM05 AC-DC 5V voltage regulator

-- Load controller --
1x MOC3021 Optocoupler
1x BT136 Triac (500V)
1x 1/2W 100 Ohms resistor
1x 1/2W 10k Ohms resistor
1x 1/2W 330 Ohms resistor
1x 100nf Ceramic capacitor