#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

int main() {
  using namespace ftxui;

   // Create a simple document with three text elements.
   Element document = hbox({
     text("DeltaFM")   | border,
     text("first basic TUI ") | border | flex,

   });

   // Create a screen with full width and height fitting the document.
   auto screen = Screen::Create(
     Dimension::Full(),       // Width
     Dimension::Fit(document) // Height
   );

   // Render the document onto the screen.
   Render(screen, document);

   // Print the screen to the console.
   screen.Print();

}
