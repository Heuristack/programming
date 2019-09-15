\version "2.18.2"

#(set-global-staff-size 30)
\paper {
  top-margin = #10
  indent = #0
}

\header {
  title = ""
  tagline = ""
}

signature = {
  \key d \minor
  \numericTimeSignature \time 3/4
}

pedal = {
  \set Staff.pedalSustainStyle = #'bracket
}

upper = \absolute {
  \clef treble
  \signature
  R4*3*2
  d'2-1 d'4-1 
  a'2-5 a'4-5
  e'4.-2 f'8-3 e'4-2
  d'2.-1
}

lower = \absolute {
  \clef bass
  \signature
  \pedal
  d4-5\sustainOn f4-3 a4-1 
  \repeat unfold 3 { d4-5 f4-3 a4-1 }
  c4-5\sustainOff\sustainOn e4-3 g4-1
  d4\sustainOff\sustainOn f4 a4
}

\score {
  \new PianoStaff <<
    \new Staff = "upper" \upper
    \new Staff = "lower" \lower
  >>
}
