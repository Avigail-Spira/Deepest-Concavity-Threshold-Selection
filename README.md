# Deepest-Concavity-Threshold-Selection

Background: One way of removing background noise in an image, or "pepper" is by using the threshold image processing. 
Thresholding the image treats anything above the threshold value to be object and anything below it is background and removed. 

Description: Not always is the threshold value given. In those cases you can use deepest concavity method to determine the best threshold value.
I created a program which uses a histogram of the given image (count of the pixel values) to determine the threshold value which will appropriately seperate object from background.

Inputs: 1. Text file representing a histogram of a gray-scale image
        2. contains four integers (representing the two peak points of the input bimodal histogram).
* Bimodal histogram is a histogram that has two peaks- one for the object and one for the background. The selected threshold should be right in the middle of both peaks.

Outputs: a file that displays the histogram, the selected threshold value, and a 2-D display of the graph that includes: histogram points, line points and gap points between the line and the
histogram.
