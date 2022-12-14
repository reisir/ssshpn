[Variables]

Bands=12
WindowFunction=Kaiser

[MeasureAudioAnalyzer]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent
Threading=Policy SeparateThread | UpdateRate 200 | WarnTime -1
Source=DefaultOutput
ProcessingUnits=Main
Unit-Main=Channels Auto | Handlers MainFFT, MainBR(MainFFT), MainBCT(MainBR), MainTR(MainBCT), MainFinalOutput(MainTR)
Handler-MainFFT=Type FFT | BinWidth 8 | OverlapBoost 10 | CascadesCount 2 | WindowFunction [#WindowFunction]
Handler-MainBR=Type BandResampler | Bands Log(Count (#Bands# + 1), FreqMin [#FreqMin], FreqMax [#FreqMax]) | CubicInterpolation true
Handler-MainBCT=Type BandCascadeTransformer | MixFunction Average | MinWeight 0.01 | TargetWeight 2 | ZeroLevelMultiplier 1
Handler-MainTR=Type TimeResampler | Attack [#FFTAttack] | Decay [#FFTDecay] | Granularity ([#UpdateRate]*2) | Transform dB, Map(From -[#MaxSensitivity] : -[#MinSensitivity]), Clamp
Handler-MainFinalOutput=Type UniformBlur | Radius [#BlurRadius] | RadiusAdaptation 1
LogUnusedOptions=false