\version "2.18.2"

author = "Lance Li"

\paper {
  top-margin = 25
% left-margin = 0
% right-margin = 0
}

\header {
  title = "Hello, LilyPond!"
  subtitle = "An Experiment on using LilyPond."
  poet = "Scales"
  composer = \author
  meter = ""
  arranger = ""
  copyright = "All rights reversed."
  tagline = "Thanks to LilyPond!"
}

setup = {
  \numericTimeSignature \time 4/4
  \override Score.BarNumber.break-visibility = #end-of-line-invisible
  \set Score.currentBarNumber = #1
  \set Score.barNumberVisibility = #(every-nth-bar-number-visible 1)
  \bar ""
}

upper = \relative {
  \clef treble
  \setup
  c' d  e  f  g  a  b  c
  c  b  a  g  f  e  d  c
  \bar "|."
}

lower = \absolute {
  \clef bass
  \time 4/4
  c  d  e  f  g  a  b  c'
  c' b  a  g  f  e  d  c
  \bar "|."
  % c' is middle c
}

\score {
  \new PianoStaff <<
    \new Staff = "upper" \upper
    \new Staff = "lower" \lower
  >>
  \header {
    piece = "C Major"
    opus = "opus"
  }
  \layout {
    #(layout-set-staff-size 28)
    indent = #35
    line-width = #180
    ragged-last = ##t
    \context {
      \PianoStaff
      % TODO: don't quite understand this context
    }
  }
  \midi {}
}

\markup {
  CDEFGAB-BAGFEDC: Lower C, Middle C, Upper C
}

