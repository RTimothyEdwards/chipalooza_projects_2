v {xschem version=3.4.5 file_version=1.2
}
G {}
K {}
V {}
S {}
E {}
T {General-purpose 2-input, 2-output switch array (1-dimensional)} -1340 -940 0 0 0.6 0.6 {}
N -450 -650 -350 -650 {
lab=channel0_in}
N -450 -480 -350 -480 {
lab=channel1_in}
N -450 -670 -350 -670 {
lab=channel0_out}
N -450 -500 -350 -500 {
lab=channel1_out}
C {devices/iopin.sym} -350 -650 0 0 {name=p7 lab=channel0_in}
C {devices/lab_pin.sym} -450 -690 0 1 {name=p13 sig_type=std_logic lab=avss}
C {devices/lab_pin.sym} -450 -630 0 1 {name=p14 sig_type=std_logic lab=avdd}
C {devices/lab_pin.sym} -450 -610 0 1 {name=p15 sig_type=std_logic lab=dvdd}
C {devices/lab_pin.sym} -450 -590 0 1 {name=p16 sig_type=std_logic lab=dvss}
C {devices/lab_pin.sym} -450 -520 0 1 {name=p17 sig_type=std_logic lab=avss}
C {devices/lab_pin.sym} -450 -460 0 1 {name=p18 sig_type=std_logic lab=avdd}
C {devices/lab_pin.sym} -450 -440 0 1 {name=p19 sig_type=std_logic lab=dvdd}
C {devices/lab_pin.sym} -450 -420 0 1 {name=p20 sig_type=std_logic lab=dvss}
C {devices/iopin.sym} -1140 -780 0 1 {name=p85 lab=avdd}
C {devices/iopin.sym} -1140 -760 0 1 {name=p86 lab=dvdd}
C {devices/iopin.sym} -1140 -740 0 1 {name=p87 lab=dvss}
C {devices/iopin.sym} -1140 -720 0 1 {name=p88 lab=avss}
C {devices/ipin.sym} -1130 -650 0 0 {name=p89 lab=channel0_in_to_out[1:0]}
C {devices/lab_pin.sym} -750 -690 0 0 {name=p90 sig_type=std_logic lab=channel0_in_to_out[0]}
C {devices/iopin.sym} -350 -670 0 0 {name=p5 lab=channel0_out}
C {devices/iopin.sym} -350 -480 0 0 {name=p6 lab=channel1_in}
C {devices/iopin.sym} -350 -500 0 0 {name=p8 lab=channel1_out}
C {devices/lab_pin.sym} -750 -670 0 0 {name=p1 sig_type=std_logic lab=channel0_in_to_out[1]}
C {devices/lab_pin.sym} -750 -520 0 0 {name=p2 sig_type=std_logic lab=channel1_in_to_out[0]}
C {devices/lab_pin.sym} -750 -500 0 0 {name=p3 sig_type=std_logic lab=channel1_in_to_out[1]}
C {devices/ipin.sym} -1130 -620 0 0 {name=p32 lab=channel1_in_to_out[1:0]}
C {isolated_switch_xlarge.sym} -600 -640 0 0 {name=x1}
C {isolated_switch_xlarge.sym} -600 -470 0 0 {name=x2}
