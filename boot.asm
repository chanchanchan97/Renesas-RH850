;   Copyright(c) 2013 Renesas Electronics Corporation
;   RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
;   This program must be used solely for the purpose for which
;   it was furnished by Renesas Electronics Corporation. No part of this
;   program may be reproduced or disclosed to others, in any
;   form, without the prior written permission of Renesas Electronics
;   Corporation.

;   NOTE       : THIS IS A TYPICAL EXAMPLE. (R7F701352AFP)

	;.extern		_INTADCA0ERR_interrupt
	.extern         _INTTAUJ0I0_interrupt
	.extern		_INTTAUJ0I1_interrupt
	.extern         _INTP1_interrupt
	.extern		_INTP12_interrupt
	;.extern		_ENCATIEC_interrupt
	;.extern		_ENCATINT0_interrupt   
	.extern         _INTRLIN1_interrupt 
	.extern		_INTRLIN30UR0_interrupt
	.extern		_INTRLIN30UR1_interrupt
	.extern		_INTRLIN30UR2_interrupt
	.extern         _INTRCAN0ERR_interrupt
	.extern         _INTRCAN0REC_interrupt
	.extern         _INTRCAN0TRX_interrupt

	.section "RESET", text
	.align	512
	jr32	__start ; RESET

	.align	16
	jr32	_Dummy ; SYSERR

	.align	16
	jr32	_Dummy ; HVTRAP

	.align	16
	jr32	_Dummy ; FETRAP

	.align	16
	jr32	_Dummy_EI ; TRAP0

	.align	16
	jr32	_Dummy_EI ; TRAP1

	.align	16
	jr32	_Dummy ; RIE

	.align	16
	jr32	_Dummy_EI ; FPP/FPI

	.align	16
	jr32	_Dummy ; UCPOP

	.align	16
	jr32	_Dummy ; MIP/MDP/ITLBE/DTLBE

	.align	16
	jr32	_Dummy ; PIE

	.align	16
	jr32	_Dummy ; Debug

	.align	16
	jr32	_Dummy ; MAE

	.align	16
	jr32	_Dummy ; (R.F.U)

	.align	16
	jr32	_Dummy ; FENMI

	.align	16
	jr32	_Dummy ; FEINT

	.align	16
	jr32	_Dummy_EI ; INTn(priority0)

	.align	16
	jr32	_Dummy_EI ; INTn(priority1)

	.align	16
	jr32	_Dummy_EI ; INTn(priority2)

	.align	16
	jr32	_Dummy_EI ; INTn(priority3)

	.align	16
	jr32	_Dummy_EI ; INTn(priority4)

	.align	16
	jr32	_Dummy_EI ; INTn(priority5)

	.align	16
	jr32	_Dummy_EI ; INTn(priority6)

	.align	16
	jr32	_Dummy_EI ; INTn(priority7)

	.section "EIINTTBL", const
	.align	512
	.dw			#_Dummy_EI								; EIINT_CH_0
	.dw			#_Dummy_EI								; EIINT_CH_1
	.dw			#_Dummy_EI								; EIINT_CH_2
	.dw			#_Dummy_EI								; EIINT_CH_3
	.dw			#_Dummy_EI								; EIINT_CH_4
	.dw			#_Dummy_EI								; EIINT_CH_5
	.dw			#_Dummy_EI								; EIINT_CH_6
	.dw			#_Dummy_EI								; EIINT_CH_7
	.dw			#_Dummy_EI								; EIINT_CH_8
	.dw			#_Dummy_EI								; EIINT_CH_9
	.dw			#_Dummy_EI								; EIINT_CH_10
	.dw			#_Dummy_EI								; EIINT_CH_11
	.dw			#_Dummy_EI								; EIINT_CH_12
	.dw			#_Dummy_EI								; EIINT_CH_13
	.dw			#_Dummy_EI								; EIINT_CH_14
	.dw			#_Dummy_EI								; EIINT_CH_15
	.dw			#_INTRCAN0ERR_interrupt								; EIINT_CH_16
	.dw			#_INTRCAN0REC_interrupt								; EIINT_CH_17
	.dw			#_INTRCAN0TRX_interrupt								; EIINT_CH_18
	.dw			#_Dummy_EI								; EIINT_CH_19
	.dw			#_Dummy_EI								; EIINT_CH_20
	.dw			#_Dummy_EI								; EIINT_CH_21
	.dw			#_Dummy_EI								; EIINT_CH_22
	.dw			#_Dummy_EI								; EIINT_CH_23
	.dw			#_Dummy_EI								; EIINT_CH_24
	.dw			#_Dummy_EI								; EIINT_CH_25
	.dw			#_INTRLIN30UR0_interrupt								; EIINT_CH_26
	.dw			#_INTRLIN30UR1_interrupt								; EIINT_CH_27
	.dw			#_INTRLIN30UR2_interrupt								; EIINT_CH_28
	.dw			#_Dummy_EI								; EIINT_CH_29
	.dw			#_INTP1_interrupt								; EIINT_CH_30
	.dw			#_Dummy_EI								; EIINT_CH_31
	.dw			#_Dummy_EI								; EIINT_CH_32
	.dw			#_Dummy_EI								; EIINT_CH_33
	.dw			#_Dummy_EI								; EIINT_CH_34
	.dw			#_Dummy_EI								; EIINT_CH_35
	.dw			#_Dummy_EI								; EIINT_CH_36
	.dw			#_Dummy_EI								; EIINT_CH_37
	.dw			#_Dummy_EI								; EIINT_CH_38
	.dw			#_Dummy_EI								; EIINT_CH_39
	.dw			#_Dummy_EI								; EIINT_CH_40
	.dw			#_Dummy_EI								; EIINT_CH_41
	.dw			#_Dummy_EI								; EIINT_CH_42
	.dw			#_Dummy_EI								; EIINT_CH_43
	.dw			#_Dummy_EI								; EIINT_CH_44
	.dw			#_Dummy_EI								; EIINT_CH_45
	.dw			#_Dummy_EI								; EIINT_CH_46
	.dw			#_Dummy_EI							        ; EIINT_CH_47
	.dw			#_Dummy_EI								; EIINT_CH_48
	.dw			#_Dummy_EI								; EIINT_CH_49
	.dw			#_Dummy_EI								; EIINT_CH_50
	.dw			#_INTRLIN1_interrupt								; EIINT_CH_51
	.dw			#_Dummy_EI								; EIINT_CH_52
	.dw			#_Dummy_EI								; EIINT_CH_53
	.dw			#_Dummy_EI								; EIINT_CH_54
	.dw			#_Dummy_EI								; EIINT_CH_55
	.dw			#_Dummy_EI								; EIINT_CH_56
	.dw			#_Dummy_EI								; EIINT_CH_57
	.dw			#_Dummy_EI								; EIINT_CH_58
	.dw			#_Dummy_EI								; EIINT_CH_59
	.dw			#_Dummy_EI								; EIINT_CH_60
	.dw			#_Dummy_EI								; EIINT_CH_61
	.dw			#_Dummy_EI								; EIINT_CH_62
	.dw			#_Dummy_EI								; EIINT_CH_63
	.dw			#_Dummy_EI								; EIINT_CH_64
	.dw			#_Dummy_EI								; EIINT_CH_65
	.dw			#_Dummy_EI								; EIINT_CH_66
	.dw			#_Dummy_EI								; EIINT_CH_67
	.dw			#_Dummy_EI								; EIINT_CH_68
	.dw			#_Dummy_EI								; EIINT_CH_69
	.dw			#_Dummy_EI								; EIINT_CH_70
	.dw			#_Dummy_EI								; EIINT_CH_71
	.dw			#_INTTAUJ0I0_interrupt								; EIINT_CH_72
	.dw			#_INTTAUJ0I1_interrupt							    ; EIINT_CH_73
	.dw			#_Dummy_EI								; EIINT_CH_74
	.dw			#_Dummy_EI								; EIINT_CH_75
	.dw			#_Dummy_EI								; EIINT_CH_76
	.dw			#_Dummy_EI								; EIINT_CH_77
	.dw			#_Dummy_EI								; EIINT_CH_78
	.dw			#_Dummy_EI								; EIINT_CH_79
	.dw			#_Dummy_EI								; EIINT_CH_80
	.dw			#_Dummy_EI								; EIINT_CH_81
	.dw			#_Dummy_EI								; EIINT_CH_82
	.dw			#_Dummy_EI								; EIINT_CH_83
	.dw			#_Dummy_EI								; EIINT_CH_84
	.dw			#_Dummy_EI								; EIINT_CH_85
	.dw			#_Dummy_EI								; EIINT_CH_86
	.dw			#_Dummy_EI								; EIINT_CH_87
	.dw			#_Dummy_EI								; EIINT_CH_88
	.dw			#_Dummy_EI								; EIINT_CH_89
	.dw			#_Dummy_EI								; EIINT_CH_90
	.dw			#_Dummy_EI								; EIINT_CH_91
	.dw			#_Dummy_EI								; EIINT_CH_92
	.dw			#_Dummy_EI								; EIINT_CH_93
	.dw			#_Dummy_EI								; EIINT_CH_94
	.dw			#_Dummy_EI								; EIINT_CH_95
	.dw			#_Dummy_EI								; EIINT_CH_96
	.dw			#_Dummy_EI								; EIINT_CH_97
	.dw			#_Dummy_EI								; EIINT_CH_98
	.dw			#_Dummy_EI								; EIINT_CH_99
	.dw			#_Dummy_EI								; EIINT_CH_100
	.dw			#_Dummy_EI								; EIINT_CH_101
	.dw			#_Dummy_EI								; EIINT_CH_102
	.dw			#_Dummy_EI								; EIINT_CH_103
	.dw			#_Dummy_EI								; EIINT_CH_104
	.dw			#_Dummy_EI								; EIINT_CH_105
	.dw			#_Dummy_EI								; EIINT_CH_106
	.dw			#_Dummy_EI								; EIINT_CH_107
	.dw			#_Dummy_EI								; EIINT_CH_108
	.dw			#_Dummy_EI								; EIINT_CH_109
	.dw			#_Dummy_EI								; EIINT_CH_110
	.dw			#_Dummy_EI								; EIINT_CH_111
	.dw			#_Dummy_EI								; EIINT_CH_112
	.dw			#_Dummy_EI								; EIINT_CH_113
	.dw			#_Dummy_EI								; EIINT_CH_114
	.dw			#_Dummy_EI								; EIINT_CH_115
	.dw			#_Dummy_EI								; EIINT_CH_116
	.dw			#_Dummy_EI								; EIINT_CH_117
	.dw			#_Dummy_EI								; EIINT_CH_118
	.dw			#_Dummy_EI								; EIINT_CH_119
	.dw			#_Dummy_EI								; EIINT_CH_120
	.dw			#_Dummy_EI								; EIINT_CH_121
	.dw			#_Dummy_EI								; EIINT_CH_122
	.dw			#_INTP12_interrupt								; EIINT_CH_123
	.dw			#_Dummy_EI								; EIINT_CH_124
	.dw			#_Dummy_EI								; EIINT_CH_125
	.dw			#_Dummy_EI								; EIINT_CH_126
	.dw			#_Dummy_EI								; EIINT_CH_127
	.dw			#_Dummy_EI								; EIINT_CH_128
	.dw			#_Dummy_EI								; EIINT_CH_129
	.dw			#_Dummy_EI								; EIINT_CH_130
	.dw			#_Dummy_EI								; EIINT_CH_131
	.dw			#_Dummy_EI								; EIINT_CH_132
	.dw			#_Dummy_EI								; EIINT_CH_133
	.dw			#_Dummy_EI								; EIINT_CH_134
	.dw			#_Dummy_EI								; EIINT_CH_135
	.dw			#_Dummy_EI								; EIINT_CH_136
	.dw			#_Dummy_EI								; EIINT_CH_137
	.dw			#_Dummy_EI								; EIINT_CH_138
	.dw			#_Dummy_EI								; EIINT_CH_139
	.dw			#_Dummy_EI								; EIINT_CH_140
	.dw			#_Dummy_EI								; EIINT_CH_141
	.dw			#_Dummy_EI								; EIINT_CH_142
	.dw			#_Dummy_EI								; EIINT_CH_143
	.dw			#_Dummy_EI								; EIINT_CH_144
	.dw			#_Dummy_EI								; EIINT_CH_145
	.dw			#_Dummy_EI								; EIINT_CH_146
	.dw			#_Dummy_EI								; EIINT_CH_147
	.dw			#_Dummy_EI								; EIINT_CH_148
	.dw			#_Dummy_EI								; EIINT_CH_149
	.dw			#_Dummy_EI								; EIINT_CH_150
	.dw			#_Dummy_EI								; EIINT_CH_151
	.dw			#_Dummy_EI								; EIINT_CH_152
	.dw			#_Dummy_EI								; EIINT_CH_153
	.dw			#_Dummy_EI								; EIINT_CH_154
	.dw			#_Dummy_EI								; EIINT_CH_155
	.dw			#_Dummy_EI								; EIINT_CH_156
	.dw			#_Dummy_EI								; EIINT_CH_157
	.dw			#_Dummy_EI								; EIINT_CH_158
	.dw			#_Dummy_EI								; EIINT_CH_159
	.dw			#_Dummy_EI								; EIINT_CH_160
	.dw			#_Dummy_EI								; EIINT_CH_161
	.dw			#_Dummy_EI								; EIINT_CH_162
	.dw			#_Dummy_EI								; EIINT_CH_163
	.dw			#_Dummy_EI								; EIINT_CH_164
	.dw			#_Dummy_EI								; EIINT_CH_165
	.dw			#_Dummy_EI								; EIINT_CH_166
	.dw			#_Dummy_EI								; EIINT_CH_167
	.dw			#_Dummy_EI								; EIINT_CH_168
	.dw			#_Dummy_EI								; EIINT_CH_169
	.dw			#_Dummy_EI								; EIINT_CH_170
	.dw			#_Dummy_EI								; EIINT_CH_171
	.dw			#_Dummy_EI								; EIINT_CH_172
	.dw			#_Dummy_EI								; EIINT_CH_173
	.dw			#_Dummy_EI								; EIINT_CH_174
	.dw			#_Dummy_EI								; EIINT_CH_175
	.dw			#_Dummy_EI								; EIINT_CH_176
	.dw			#_Dummy_EI								; EIINT_CH_177
	.dw			#_Dummy_EI								; EIINT_CH_178
	.dw			#_Dummy_EI								; EIINT_CH_179
	.dw			#_Dummy_EI								; EIINT_CH_180
	.dw			#_Dummy_EI								; EIINT_CH_181
	.dw			#_Dummy_EI								; EIINT_CH_182
	.dw			#_Dummy_EI								; EIINT_CH_183
	.dw			#_Dummy_EI								; EIINT_CH_184
	.dw			#_Dummy_EI								; EIINT_CH_185
	.dw			#_Dummy_EI								; EIINT_CH_186
	.dw			#_Dummy_EI								; EIINT_CH_187
	.dw			#_Dummy_EI								; EIINT_CH_188
	.dw			#_Dummy_EI								; EIINT_CH_189
	.dw			#_Dummy_EI								; EIINT_CH_190
	.dw			#_Dummy_EI								; EIINT_CH_191
	.dw			#_Dummy_EI								; EIINT_CH_192
	.dw			#_Dummy_EI								; EIINT_CH_193
	.dw			#_Dummy_EI								; EIINT_CH_194
	.dw			#_Dummy_EI								; EIINT_CH_195
	.dw			#_Dummy_EI								; EIINT_CH_196
	.dw			#_Dummy_EI								; EIINT_CH_197
	.dw			#_Dummy_EI								; EIINT_CH_198
	.dw			#_Dummy_EI								; EIINT_CH_199
	.dw			#_Dummy_EI								; EIINT_CH_200
	.dw			#_Dummy_EI								; EIINT_CH_201
	.dw			#_Dummy_EI								; EIINT_CH_202
	.dw			#_Dummy_EI								; EIINT_CH_203
	.dw			#_Dummy_EI								; EIINT_CH_204
	.dw			#_Dummy_EI								; EIINT_CH_205
	.dw			#_Dummy_EI								; EIINT_CH_206
	.dw			#_Dummy_EI								; EIINT_CH_207
	.dw			#_Dummy_EI								; EIINT_CH_208
	.dw			#_Dummy_EI								; EIINT_CH_209
	.dw			#_Dummy_EI								; EIINT_CH_210
	.dw			#_Dummy_EI								; EIINT_CH_211
	.dw			#_Dummy_EI								; EIINT_CH_212
	.dw			#_Dummy_EI								; EIINT_CH_213
	.dw			#_Dummy_EI								; EIINT_CH_214
	.dw			#_Dummy_EI								; EIINT_CH_215
	.dw			#_Dummy_EI								; EIINT_CH_216
	.dw			#_Dummy_EI								; EIINT_CH_217
	.dw			#_Dummy_EI								; EIINT_CH_218
	.dw			#_Dummy_EI								; EIINT_CH_219
	.dw			#_Dummy_EI								; EIINT_CH_220
	.dw			#_Dummy_EI								; EIINT_CH_221
	.dw			#_Dummy_EI								; EIINT_CH_222
	.dw			#_Dummy_EI								; EIINT_CH_223
	.dw			#_Dummy_EI								; EIINT_CH_224
	.dw			#_Dummy_EI								; EIINT_CH_225
	.dw			#_Dummy_EI								; EIINT_CH_226
	.dw			#_Dummy_EI								; EIINT_CH_227
	.dw			#_Dummy_EI								; EIINT_CH_228
	.dw			#_Dummy_EI								; EIINT_CH_229
	.dw			#_Dummy_EI								; EIINT_CH_230
	.dw			#_Dummy_EI								; EIINT_CH_231
	.dw			#_Dummy_EI								; EIINT_CH_232
	.dw			#_Dummy_EI								; EIINT_CH_233
	.dw			#_Dummy_EI								; EIINT_CH_234
	.dw			#_Dummy_EI								; EIINT_CH_235
	.dw			#_Dummy_EI								; EIINT_CH_236
	.dw			#_Dummy_EI								; EIINT_CH_237
	.dw			#_Dummy_EI								; EIINT_CH_238
	.dw			#_Dummy_EI								; EIINT_CH_239
	.dw			#_Dummy_EI								; EIINT_CH_240
	.dw			#_Dummy_EI								; EIINT_CH_241
	.dw			#_Dummy_EI								; EIINT_CH_242
	.dw			#_Dummy_EI								; EIINT_CH_243
	.dw			#_Dummy_EI								; EIINT_CH_244
	.dw			#_Dummy_EI								; EIINT_CH_245
	.dw			#_Dummy_EI								; EIINT_CH_246
	.dw			#_Dummy_EI								; EIINT_CH_247
	.dw			#_Dummy_EI								; EIINT_CH_248
	.dw			#_Dummy_EI								; EIINT_CH_249
	.dw			#_Dummy_EI								; EIINT_CH_250
	.dw			#_Dummy_EI								; EIINT_CH_251
	.dw			#_Dummy_EI								; EIINT_CH_252
	.dw			#_Dummy_EI								; EIINT_CH_253
	.dw			#_Dummy_EI								; EIINT_CH_254
	.dw			#_Dummy_EI								; EIINT_CH_255
	.dw			#_Dummy_EI								; EIINT_CH_256
	.dw			#_Dummy_EI								; EIINT_CH_257
	.dw			#_Dummy_EI								; EIINT_CH_258
	.dw			#_Dummy_EI								; EIINT_CH_259
	.dw			#_Dummy_EI								; EIINT_CH_260
	.dw			#_Dummy_EI								; EIINT_CH_261
	.dw			#_Dummy_EI								; EIINT_CH_262
	.dw			#_Dummy_EI								; EIINT_CH_263
	.dw			#_Dummy_EI								; EIINT_CH_264
	.dw			#_Dummy_EI								; EIINT_CH_265
	.dw			#_Dummy_EI								; EIINT_CH_266
	.dw			#_Dummy_EI								; EIINT_CH_267
	.dw			#_Dummy_EI								; EIINT_CH_268
	.dw			#_Dummy_EI								; EIINT_CH_269
	.dw			#_Dummy_EI								; EIINT_CH_270
	.dw			#_Dummy_EI								; EIINT_CH_271
	.dw			#_Dummy_EI								; EIINT_CH_272
	.dw			#_Dummy_EI								; EIINT_CH_273
	.dw			#_Dummy_EI								; EIINT_CH_274
	.dw			#_Dummy_EI								; EIINT_CH_275
	.dw			#_Dummy_EI								; EIINT_CH_276
	.dw			#_Dummy_EI								; EIINT_CH_277
	.dw			#_Dummy_EI								; EIINT_CH_278
	.dw			#_Dummy_EI								; EIINT_CH_279
	.dw			#_Dummy_EI								; EIINT_CH_280
	.dw			#_Dummy_EI								; EIINT_CH_281
	.dw			#_Dummy_EI								; EIINT_CH_282
	.dw			#_Dummy_EI								; EIINT_CH_283
	.dw			#_Dummy_EI								; EIINT_CH_284
	.dw			#_Dummy_EI								; EIINT_CH_285
	.dw			#_Dummy_EI								; EIINT_CH_286
	.dw			#_Dummy_EI								; EIINT_CH_287

	.section ".text", text
	.align	2
_Dummy:
	br	_Dummy

_Dummy_EI:
	br	_Dummy_EI
