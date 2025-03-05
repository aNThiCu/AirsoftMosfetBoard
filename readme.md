This is untested , unstable hardware. The main focus of this version was creating more room for upgrades and manufacturability at home.

The hardware now consists of 2 PCB's one being the control center and the other the necessary sensors. This makes the board be less prone to shorts or mechanical stress from the gearbox of the replica.
The control board will sit inside the buffer tube while the sensor board will stay in the same position.

Being able to make the PCB's at home saves a whole lot of time so the following changes have been made:

    -thick traces of 0.5 width and up , resulting in the need of a less precise CNC
    -most of the traces are only on the front side , thanks to splitting the components across 2 boards
    -components added/modified for protection and well functioning of the boards
    -switched from 5V LDO to 3.3V buck , microcontroller shouldn't reset anymore while using low discharge rate battery

 What's coming next (hopefully):

    -configurable mode selector switch with multiple modes
    -app for ease of use (mby)
    -troubleshooting indicators
    -folder with everything needed for direct manufacturing from a factory
    -different trigger version (optical/magnetic)
    -stress testing results
    -redo of shape for better fitment in V2 gearboxes
