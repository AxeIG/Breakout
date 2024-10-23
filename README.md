# Breakout

A/D to move paddle left and right
P to pause
Left click on the paddle to drag it around

PowerUps:
Slow/Fast (purple) affects the ball's speed
Big/Small (white) affects the paddle's size
FireBall (red) allows ball to break through bricks without bouncing
StickyBall (green) sticks the ball to the paddle on collision, press the scroll wheel to launch the ball forwards

For the breakout application I have fixed the compiler issues and added the StickyBall power up, modified the PowerUp manager into a static class and added the option to directly change the flaot variable the power-up in effect holds to allow the creation of non time-reliant powerups withotu creating a new structure.
Particles can be added onto the screen, and along with a particle manager I have implemented a trail for the ball and a "dust" effect for ball collisions with the paddle and bricks.
For additional controls the player can now drag the paddle using the left mouse button, and a slider has been added to the power up informative text for a nicer representation of the remaining time.


Breakout contributions:
Fixed compiler errors and small bugs : 30 minutes
 -child class PowerupFireBall included in parent class which caused definition errors
 -powerup colours are now correctly assigned
 -changed variable names for better clarity
                
MouseDrag and UI: 1 hour   
-added mouse input for paddle movement
-added slider for the powerUp timer

VFX: 2 hours
-Added particles: customisable rectangle shapes that follow a life-span;
-Through a particle manager they are being used for creating the ball trail and the dust particles on ball bounce

StickyBall PowerUp: 1 hour
-Added a stickyball powerup that allows the ball to stick to the paddle and then be lunched upwards whenever the player wants.
-The powerup has no time limit, the effect ends once the player has launched the ball.
-The PowerUp Manager class has been made static so it can be more easly used by outside classes

Imrpoved random powerup spawn: 10 minutes

Added ScreenShake: 5 minutes
-on life loss the window will shake around and return to the original position

Total Worktime: 4:45 hours

