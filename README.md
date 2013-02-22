Makinator
=========

This is my take on a (relatively) large 3D printer I'm calling the Makinator. I seriously considered a few other options before deciding on building a custom design, these include the [MendelMax](http://www.mendelmax.com/), the [Ordbot](http://www.buildlog.net/blog/2012/01/the-quantum-ord-bot/), and then the [Eventorbot](http://www.eventorbot.com/). But as much as I understand the idea around separating the X and Y axis for inertial reasons, it doesn't scale well because the machine has to be twice as big as the print bed, and I wanted a much bigger printer.

Design Considerations:
----------------------
- Super large print area. As much as I wanted a 4 foot area like the [BigBot](http://www.thingiverse.com/thing:24037), because of space considerations I finally decided on a conservative 600mm x 600mm x 600mm (~24in).
- Maximum size to print area ratio. I designed the X/Y gantry to ride over top of the frame so the print head could come as close to the outer edge as possible and increase the usable amount of area.
- No printed parts. This is my first 3D printer so I didn't have easy access to custom plastic parts. I had to figure out how to make everything by hand or find them off the shelf.
- Robustness. I will also be using it as a cnc machine to mill wood and metal so it needed to be very strong.

It uses [Open Rail](http://www.kickstarter.com/projects/openrail/openrail-open-source-linear-bearing-system) for the Y axis linear bearings, which allows the gantry system to carry more weight than smooth rods would allow. For the X axis linear bearings it uses two 10mm smooth rods, this lets the print head (or any other tool I can fit in there) sit centered between them and get as close to the outside as possible. The Z axis uses low friction PTFE (teflon) slides for strength and low cost, they will ride in grooves cut the square tubing.

![Early Animation](https://github.com/knickers/makinator/blob/master/makinator-small.gif?raw=true)
![Early Rendering](http://blog.infosiftr.com/wp-content/uploads/2012/08/makinator-07.png)
