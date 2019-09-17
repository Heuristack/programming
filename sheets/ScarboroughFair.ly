\version "2.18.2"

#(set-global-staff-size 22)

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

measure = {
  \override Score.BarNumber.break-visibility = #end-of-line-invisible
  \override Score.BarNumber.self-alignment-X = #LEFT
  \override Score.BarNumber.font-size = #0.5
  \override Score.BarNumber.stencil
    = #(make-stencil-circler 0.2 0.2 ly:text-interface::print)
  \set Score.currentBarNumber = #1
  \set Score.barNumberVisibility = #(every-nth-bar-number-visible 1)
}

upper = \absolute {
  \clef treble
  \signature
  R4*3*2
  \measure
  d'2-1 d'4-1 a'2-5 a'4 -5
  e'4.-2 f'8-3 e'4-2 d'2.-1 (d'4-1)
  a'4-2 c''4-4 d''2-5 c''4-4 a'4-2 
  b'4-3 g'4-1 a'2.-2
}

lower = \absolute {
  \clef bass
  \signature
  \pedal
  d4-5\sustainOn f4-3 a4-1 \repeat unfold 3 { d4-5 f4-3 a4-1 }
  c4-5\sustainOff\sustainOn e4-3 g4-1
  d4-5\sustainOff\sustainOn f4-3 a4-1
  d4-5 f4-3 a4-1
  d4-5\sustainOff\sustainOn f4-3 a4-1
  d4-5\sustainOff\sustainOn g4-2 b4-1
  d4-5\sustainOff\sustainOn f4-3 a4-1
}

\score {
  \new PianoStaff <<
    \new Staff = "upper" \upper
    \new Staff = "lower" \lower
  >>
  \header {
    piece = "Scarborough Fair"
    opus = "Week 38 2019"
  }
  \layout {
  }
}
\markup {
  Sing: DD-AA-EF-ED ACD-CA-BGA
}
\markup {}
\markup {}
\markup {}
\markup {}

upper_today = \absolute {
  \clef treble
  \signature
  \bar ""
  \measure
  a'2 
  d''4-5 d''2-5 
  d''4-5 c''2-4 a'4-2
  a'4-3 g'4 f'4-1
  e'2.-2 (e'2.-2)
}

lower_today = \absolute {
  \clef bass
  \signature
  \pedal
  d4-5\sustainOn f4-3 a4-1
  d4-5\sustainOff\sustainOn f4-3 a4-1
  c4-5\sustainOff\sustainOn f4-2 a4-1
  f4-2\sustainOff e4-3 d4-4
  c4-5\sustainOn e4-3 g4-1
  c4-5 e4-3 g4-1
}

\score {
  \new PianoStaff <<
    \new Staff = "upper" \upper_today
    \new Staff = "lower" \lower_today
  >>
  \header {
    piece = "Wednesday"
    opus = "09/18/2019"
  }
}
\markup {
  Sing: DD-DC-AA-GFE
}

