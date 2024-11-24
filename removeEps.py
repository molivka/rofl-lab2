from FAdo.fa import NFA, DFA,Epsilon
nfa = NFA()
nfa.addInitial(2)
nfa.addFinal(131)
nfa.addFinal(133)
nfa.addState(0)
nfa.addTransition(0,Epsilon , 1)
nfa.addTransition(0,Epsilon , 5)
nfa.addState(1)
nfa.addTransition(1, 3, 0)
nfa.addState(2)
nfa.addTransition(2,Epsilon , 1)
nfa.addTransition(2,Epsilon , 5)
nfa.addState(3)
nfa.addTransition(3,Epsilon , 4)
nfa.addTransition(3,Epsilon , 127)
nfa.addState(4)
nfa.addTransition(4, 3, 3)
nfa.addState(5)
nfa.addTransition(5,Epsilon , 4)
nfa.addTransition(5,Epsilon , 127)
nfa.addState(6)
nfa.addTransition(6, 2, 7)
nfa.addState(7)
nfa.addTransition(7,Epsilon , 130)
nfa.addTransition(7, 1, 7)
nfa.addTransition(7, 2, 7)
nfa.addTransition(7, 6, 7)
nfa.addTransition(7, 7, 6)
nfa.addState(127)
nfa.addTransition(127,Epsilon , 7)
nfa.addTransition(127,Epsilon , 10)
nfa.addTransition(127,Epsilon , 115)
nfa.addState(8)
nfa.addTransition(8,Epsilon , 13)
nfa.addState(9)
nfa.addTransition(9, 7, 8)
nfa.addState(10)
nfa.addTransition(10, 1, 9)
nfa.addTransition(10, 5, 9)
nfa.addTransition(10, 6, 9)
nfa.addTransition(10, 8, 9)
nfa.addState(11)
nfa.addTransition(11,Epsilon , 12)
nfa.addTransition(11,Epsilon , 55)
nfa.addState(12)
nfa.addTransition(12, 3, 11)
nfa.addState(13)
nfa.addTransition(13,Epsilon , 12)
nfa.addTransition(13,Epsilon , 55)
nfa.addState(14)
nfa.addTransition(14, 2, 15)
nfa.addState(15)
nfa.addTransition(15,Epsilon , 58)
nfa.addTransition(15, 1, 15)
nfa.addTransition(15, 2, 15)
nfa.addTransition(15, 6, 15)
nfa.addTransition(15, 7, 14)
nfa.addState(55)
nfa.addTransition(55,Epsilon , 15)
nfa.addTransition(55,Epsilon , 18)
nfa.addTransition(55,Epsilon , 43)
nfa.addState(16)
nfa.addTransition(16,Epsilon , 21)
nfa.addState(17)
nfa.addTransition(17, 7, 16)
nfa.addState(18)
nfa.addTransition(18, 1, 17)
nfa.addTransition(18, 5, 17)
nfa.addTransition(18, 6, 17)
nfa.addTransition(18, 8, 17)
nfa.addState(19)
nfa.addTransition(19,Epsilon , 20)
nfa.addTransition(19,Epsilon , 23)
nfa.addState(20)
nfa.addTransition(20, 3, 19)
nfa.addState(21)
nfa.addTransition(21,Epsilon , 20)
nfa.addTransition(21,Epsilon , 23)
nfa.addState(22)
nfa.addTransition(22, 2, 23)
nfa.addState(23)
nfa.addTransition(23,Epsilon , 26)
nfa.addTransition(23, 1, 23)
nfa.addTransition(23, 2, 23)
nfa.addTransition(23, 6, 23)
nfa.addTransition(23, 7, 22)
nfa.addState(24)
nfa.addTransition(24,Epsilon , 25)
nfa.addTransition(24,Epsilon , 28)
nfa.addState(25)
nfa.addTransition(25, 3, 24)
nfa.addState(26)
nfa.addTransition(26,Epsilon , 25)
nfa.addTransition(26,Epsilon , 28)
nfa.addState(27)
nfa.addTransition(27,Epsilon , 32)
nfa.addState(28)
nfa.addTransition(28, 5, 27)
nfa.addTransition(28, 7, 27)
nfa.addState(29)
nfa.addTransition(29, 0, 28)
nfa.addTransition(29, 2, 28)
nfa.addTransition(29, 4, 28)
nfa.addTransition(29, 5, 28)
nfa.addTransition(29, 6, 28)
nfa.addTransition(29, 8, 28)
nfa.addState(30)
nfa.addTransition(30,Epsilon , 31)
nfa.addTransition(30,Epsilon , 34)
nfa.addState(31)
nfa.addTransition(31, 3, 30)
nfa.addState(32)
nfa.addTransition(32,Epsilon , 31)
nfa.addTransition(32,Epsilon , 34)
nfa.addState(33)
nfa.addTransition(33, 2, 34)
nfa.addState(34)
nfa.addTransition(34,Epsilon , 37)
nfa.addTransition(34, 1, 34)
nfa.addTransition(34, 2, 34)
nfa.addTransition(34, 6, 34)
nfa.addTransition(34, 7, 33)
nfa.addState(35)
nfa.addTransition(35,Epsilon , 36)
nfa.addTransition(35,Epsilon , 39)
nfa.addState(36)
nfa.addTransition(36, 3, 35)
nfa.addState(37)
nfa.addTransition(37,Epsilon , 36)
nfa.addTransition(37,Epsilon , 39)
nfa.addTransition(37,Epsilon , 58)
nfa.addState(38)
nfa.addState(39)
nfa.addTransition(39, 5, 38)
nfa.addState(40)
nfa.addTransition(40, 0, 39)
nfa.addTransition(40, 1, 39)
nfa.addTransition(40, 4, 39)
nfa.addTransition(40, 5, 38)
nfa.addTransition(40, 6, 39)
nfa.addTransition(40, 8, 38)
nfa.addState(41)
nfa.addTransition(41,Epsilon , 46)
nfa.addState(42)
nfa.addTransition(42, 7, 41)
nfa.addState(43)
nfa.addTransition(43, 1, 42)
nfa.addTransition(43, 5, 42)
nfa.addTransition(43, 6, 42)
nfa.addTransition(43, 8, 42)
nfa.addState(44)
nfa.addTransition(44,Epsilon , 45)
nfa.addTransition(44,Epsilon , 48)
nfa.addState(45)
nfa.addTransition(45, 3, 44)
nfa.addState(46)
nfa.addTransition(46,Epsilon , 45)
nfa.addTransition(46,Epsilon , 48)
nfa.addState(47)
nfa.addTransition(47, 2, 48)
nfa.addState(48)
nfa.addTransition(48,Epsilon , 51)
nfa.addTransition(48, 1, 48)
nfa.addTransition(48, 2, 48)
nfa.addTransition(48, 6, 48)
nfa.addTransition(48, 7, 47)
nfa.addState(49)
nfa.addTransition(49,Epsilon , 50)
nfa.addTransition(49,Epsilon , 46)
nfa.addTransition(49,Epsilon , 53)
nfa.addState(50)
nfa.addTransition(50, 3, 49)
nfa.addState(51)
nfa.addTransition(51,Epsilon , 50)
nfa.addTransition(51,Epsilon , 46)
nfa.addTransition(51,Epsilon , 53)
nfa.addTransition(51,Epsilon , 58)
nfa.addState(52)
nfa.addState(53)
nfa.addTransition(53, 5, 52)
nfa.addState(54)
nfa.addTransition(54, 0, 53)
nfa.addTransition(54, 1, 53)
nfa.addTransition(54, 4, 53)
nfa.addTransition(54, 5, 52)
nfa.addTransition(54, 6, 53)
nfa.addTransition(54, 8, 52)
nfa.addState(56)
nfa.addTransition(56,Epsilon , 57)
nfa.addTransition(56,Epsilon , 60)
nfa.addState(57)
nfa.addTransition(57, 3, 56)
nfa.addState(58)
nfa.addTransition(58,Epsilon , 57)
nfa.addTransition(58,Epsilon , 60)
nfa.addState(59)
nfa.addTransition(59,Epsilon , 64)
nfa.addState(60)
nfa.addTransition(60, 5, 59)
nfa.addTransition(60, 7, 59)
nfa.addState(61)
nfa.addTransition(61, 0, 60)
nfa.addTransition(61, 2, 60)
nfa.addTransition(61, 4, 60)
nfa.addTransition(61, 5, 60)
nfa.addTransition(61, 6, 60)
nfa.addTransition(61, 8, 60)
nfa.addState(62)
nfa.addTransition(62,Epsilon , 63)
nfa.addTransition(62,Epsilon , 106)
nfa.addState(63)
nfa.addTransition(63, 3, 62)
nfa.addState(64)
nfa.addTransition(64,Epsilon , 63)
nfa.addTransition(64,Epsilon , 106)
nfa.addState(65)
nfa.addTransition(65, 2, 66)
nfa.addState(66)
nfa.addTransition(66,Epsilon , 109)
nfa.addTransition(66, 1, 66)
nfa.addTransition(66, 2, 66)
nfa.addTransition(66, 6, 66)
nfa.addTransition(66, 7, 65)
nfa.addState(106)
nfa.addTransition(106,Epsilon , 66)
nfa.addTransition(106,Epsilon , 69)
nfa.addTransition(106,Epsilon , 94)
nfa.addState(67)
nfa.addTransition(67,Epsilon , 72)
nfa.addState(68)
nfa.addTransition(68, 7, 67)
nfa.addState(69)
nfa.addTransition(69, 1, 68)
nfa.addTransition(69, 5, 68)
nfa.addTransition(69, 6, 68)
nfa.addTransition(69, 8, 68)
nfa.addState(70)
nfa.addTransition(70,Epsilon , 71)
nfa.addTransition(70,Epsilon , 74)
nfa.addState(71)
nfa.addTransition(71, 3, 70)
nfa.addState(72)
nfa.addTransition(72,Epsilon , 71)
nfa.addTransition(72,Epsilon , 74)
nfa.addState(73)
nfa.addTransition(73, 2, 74)
nfa.addState(74)
nfa.addTransition(74,Epsilon , 77)
nfa.addTransition(74, 1, 74)
nfa.addTransition(74, 2, 74)
nfa.addTransition(74, 6, 74)
nfa.addTransition(74, 7, 73)
nfa.addState(75)
nfa.addTransition(75,Epsilon , 76)
nfa.addTransition(75,Epsilon , 79)
nfa.addState(76)
nfa.addTransition(76, 3, 75)
nfa.addState(77)
nfa.addTransition(77,Epsilon , 76)
nfa.addTransition(77,Epsilon , 79)
nfa.addState(78)
nfa.addTransition(78,Epsilon , 83)
nfa.addState(79)
nfa.addTransition(79, 5, 78)
nfa.addTransition(79, 7, 78)
nfa.addState(80)
nfa.addTransition(80, 0, 79)
nfa.addTransition(80, 2, 79)
nfa.addTransition(80, 4, 79)
nfa.addTransition(80, 5, 79)
nfa.addTransition(80, 6, 79)
nfa.addTransition(80, 8, 79)
nfa.addState(81)
nfa.addTransition(81,Epsilon , 82)
nfa.addTransition(81,Epsilon , 85)
nfa.addState(82)
nfa.addTransition(82, 3, 81)
nfa.addState(83)
nfa.addTransition(83,Epsilon , 82)
nfa.addTransition(83,Epsilon , 85)
nfa.addState(84)
nfa.addTransition(84, 2, 85)
nfa.addState(85)
nfa.addTransition(85,Epsilon , 88)
nfa.addTransition(85, 1, 85)
nfa.addTransition(85, 2, 85)
nfa.addTransition(85, 6, 85)
nfa.addTransition(85, 7, 84)
nfa.addState(86)
nfa.addTransition(86,Epsilon , 87)
nfa.addTransition(86,Epsilon , 90)
nfa.addState(87)
nfa.addTransition(87, 3, 86)
nfa.addState(88)
nfa.addTransition(88,Epsilon , 87)
nfa.addTransition(88,Epsilon , 90)
nfa.addTransition(88,Epsilon , 109)
nfa.addState(89)
nfa.addState(90)
nfa.addTransition(90, 5, 89)
nfa.addState(91)
nfa.addTransition(91, 0, 90)
nfa.addTransition(91, 1, 90)
nfa.addTransition(91, 4, 90)
nfa.addTransition(91, 5, 89)
nfa.addTransition(91, 6, 90)
nfa.addTransition(91, 8, 89)
nfa.addState(92)
nfa.addTransition(92,Epsilon , 97)
nfa.addState(93)
nfa.addTransition(93, 7, 92)
nfa.addState(94)
nfa.addTransition(94, 1, 93)
nfa.addTransition(94, 5, 93)
nfa.addTransition(94, 6, 93)
nfa.addTransition(94, 8, 93)
nfa.addState(95)
nfa.addTransition(95,Epsilon , 96)
nfa.addTransition(95,Epsilon , 99)
nfa.addState(96)
nfa.addTransition(96, 3, 95)
nfa.addState(97)
nfa.addTransition(97,Epsilon , 96)
nfa.addTransition(97,Epsilon , 99)
nfa.addState(98)
nfa.addTransition(98, 2, 99)
nfa.addState(99)
nfa.addTransition(99,Epsilon , 102)
nfa.addTransition(99, 1, 99)
nfa.addTransition(99, 2, 99)
nfa.addTransition(99, 6, 99)
nfa.addTransition(99, 7, 98)
nfa.addState(100)
nfa.addTransition(100,Epsilon , 101)
nfa.addTransition(100,Epsilon , 97)
nfa.addTransition(100,Epsilon , 104)
nfa.addState(101)
nfa.addTransition(101, 3, 100)
nfa.addState(102)
nfa.addTransition(102,Epsilon , 101)
nfa.addTransition(102,Epsilon , 97)
nfa.addTransition(102,Epsilon , 104)
nfa.addTransition(102,Epsilon , 109)
nfa.addState(103)
nfa.addState(104)
nfa.addTransition(104, 5, 103)
nfa.addState(105)
nfa.addTransition(105, 0, 104)
nfa.addTransition(105, 1, 104)
nfa.addTransition(105, 4, 104)
nfa.addTransition(105, 5, 103)
nfa.addTransition(105, 6, 104)
nfa.addTransition(105, 8, 103)
nfa.addState(107)
nfa.addTransition(107,Epsilon , 108)
nfa.addTransition(107,Epsilon , 111)
nfa.addState(108)
nfa.addTransition(108, 3, 107)
nfa.addState(109)
nfa.addTransition(109,Epsilon , 108)
nfa.addTransition(109,Epsilon , 111)
nfa.addTransition(109,Epsilon , 130)
nfa.addState(110)
nfa.addState(111)
nfa.addTransition(111, 5, 110)
nfa.addState(112)
nfa.addTransition(112, 0, 111)
nfa.addTransition(112, 1, 111)
nfa.addTransition(112, 4, 111)
nfa.addTransition(112, 5, 110)
nfa.addTransition(112, 6, 111)
nfa.addTransition(112, 8, 110)
nfa.addState(113)
nfa.addTransition(113,Epsilon , 118)
nfa.addState(114)
nfa.addTransition(114, 7, 113)
nfa.addState(115)
nfa.addTransition(115, 1, 114)
nfa.addTransition(115, 5, 114)
nfa.addTransition(115, 6, 114)
nfa.addTransition(115, 8, 114)
nfa.addState(116)
nfa.addTransition(116,Epsilon , 117)
nfa.addTransition(116,Epsilon , 120)
nfa.addState(117)
nfa.addTransition(117, 3, 116)
nfa.addState(118)
nfa.addTransition(118,Epsilon , 117)
nfa.addTransition(118,Epsilon , 120)
nfa.addState(119)
nfa.addTransition(119, 2, 120)
nfa.addState(120)
nfa.addTransition(120,Epsilon , 123)
nfa.addTransition(120, 1, 120)
nfa.addTransition(120, 2, 120)
nfa.addTransition(120, 6, 120)
nfa.addTransition(120, 7, 119)
nfa.addState(121)
nfa.addTransition(121,Epsilon , 122)
nfa.addTransition(121,Epsilon , 118)
nfa.addTransition(121,Epsilon , 125)
nfa.addState(122)
nfa.addTransition(122, 3, 121)
nfa.addState(123)
nfa.addTransition(123,Epsilon , 122)
nfa.addTransition(123,Epsilon , 118)
nfa.addTransition(123,Epsilon , 125)
nfa.addTransition(123,Epsilon , 130)
nfa.addState(124)
nfa.addState(125)
nfa.addTransition(125, 5, 124)
nfa.addState(126)
nfa.addTransition(126, 0, 125)
nfa.addTransition(126, 1, 125)
nfa.addTransition(126, 4, 125)
nfa.addTransition(126, 5, 124)
nfa.addTransition(126, 6, 125)
nfa.addTransition(126, 8, 124)
nfa.addState(128)
nfa.addTransition(128,Epsilon , 129)
nfa.addTransition(128,Epsilon , 133)
nfa.addState(129)
nfa.addTransition(129, 3, 128)
nfa.addState(130)
nfa.addTransition(130,Epsilon , 129)
nfa.addTransition(130,Epsilon , 133)
nfa.addState(131)
nfa.addTransition(131,Epsilon , 132)
nfa.addTransition(131,Epsilon , 5)
nfa.addState(132)
nfa.addTransition(132, 3, 131)
nfa.addState(133)
nfa.addTransition(133,Epsilon , 132)
nfa.addTransition(133,Epsilon , 5)
dfa = nfa.elimEpsilon()
trim = nfa.trim()
dfa = trim.toDFA()
print(dfa.Initial)
print(len(dfa.Final))
for x in dfa.Final:
    print(x)

transitions = nfa.transitions()
states = nfa.States
symbols = set()
for transition in transitions:
    symbols.add(transition[1])
    state_from = transition[0]
    symbol = transition[1]
    state_to = transition[2]
    print(state_from, symbol, state_to)
