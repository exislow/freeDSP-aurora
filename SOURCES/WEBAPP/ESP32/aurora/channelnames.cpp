#include <Arduino.h>
#include <SPIFFS.h>

#include "config.h"
#include "plugin.h"
#include "channelnames.h"

String channelNames[NUMCHANNELNAMES];
String presetNames[NUMPRESETS];

//==============================================================================
/*! Write the channel names to file.
 */
void writeChannelNames(void)
{
  Serial.println("writeChannelNames");
  File file = SPIFFS.open("/chnames.txt", FILE_WRITE);
 
  if(!file)
  {
    Serial.println(F("[ERROR] writeChannelNames(): Open channels.txt failed."));
    return;
  }

  for(int ii = 0; numInputs + numOutputs && ii < NUMCHANNELNAMES; ii++)
    file.print(channelNames[ii] + String("\n"));
  for(int ii = 0; ii < NUMPRESETS; ii++)
    file.print(presetNames[ii] + String("\n"));

  file.close();
}

//==============================================================================
/*! Reads the channel names from file.
 */
void readChannelNames(void)
{
  File file = SPIFFS.open("/chnames.txt", FILE_READ);
 
  if(!file)
  {
    Serial.println(F("[ERROR] readChannelNames(): Open channels.txt failed."));
    return;
  }

  int ii = 0;
  while(file.available())
  {
    String str = file.readStringUntil('\n');
    if(ii < numInputs + numOutputs && ii < NUMCHANNELNAMES)
      channelNames[ii] = str;
    else if(ii < numInputs + numOutputs + NUMPRESETS)
      presetNames[ii - numInputs - numOutputs] = str;
    ii++;
  }

  file.close();
}
  

//==============================================================================
/*! Creates a page for editing the channel names
 *
 */
String createChannelNamesPage(void)
{ 
  String ret;

  ret = R""""(
    <!DOCTYPE html>
    <html lang="en">
    <meta name="viewport" content="width=device-width, initial-scale=1" charset="utf-8">
    <head>
    <title>i:3 Audio DSP</title>
    <link id='theme' rel="stylesheet" href="dark.css" rel="stylesheet" type="text/css">
    <script type="text/javascript" src="aurora.js"></script>
    </head>
    <body>
    <center><div style="border-bottom: 1px solid; width: 25%"><h1>Aurora</h1></div></center>
    <div><h2>Names</h2></div>)"""";

  ret += String("<table><tr><td id='audioinputs' data-numchannels='") + String(numInputs) + String("'>Audio Inputs</td>");
  ret += String("<td id='audiooutputs' data-numchannels='") + String(numOutputs) + String("'>Audio Outputs</td>");
  ret += String("<td id='presets' data-numpresets='") + String(NUMPRESETS) + String("'>Presets</td>");
  ret += String("</tr>");

  // Audio Input Names
  ret += String("<tr style='vertical-align:top'><td>");
  ret += String("<table>");
  for(int ii = 0; ii < numInputs; ii++)
    ret += String("<tr><td> Input #") + String(ii + 1) + String("</td>")
         + String("<td><input type='text' id='input") + String(ii) + String("' value='") + channelNames[ii] + String("'></td></tr>");
  ret += String("</table>");

  // Audio Output Names
  ret += String("</td><td>");
  ret += String("<table>");
  for(int ii = 0; ii < numOutputs; ii++)
  {
    ret += String("<tr><td> Output #") + String(ii + 1) + String("</td>")
         + String("<td><input type='text' id='output") + String(ii) + String("' value='") + channelNames[numInputs + ii] + String("'></td></tr>");

  }
  ret += String("</table>");

  // Preset Names
  ret += String("</td><td>");
  ret += String("<table>");
  for(int ii = 0; ii < NUMPRESETS; ii++)
    ret += String("<tr><td> Preset #") + String(ii + 1) + String("</td>")
         + String("<td><input type='text' id='preset") + String(ii) + String("' value='") + presetNames[ii] + String("'></td></tr>");
  ret += String("</table>");

  ret += String("</td>");
  ret += String("</tr></table>");

  ret += R""""(
  <center>
    <table><tr>
      <td><button class="cfgbtn" style="height:30px;" id="cfgcancel" onclick="window.location.href='/'">Cancel</button></td>
      <td><button class="cfgbtn" style="height:30px;" id="cfgstore" onclick="onStoreNames()">Store</button></td>
    </tr></table>
    </center>
  )"""";

  ret += "</body></html>";

  return ret;
}
