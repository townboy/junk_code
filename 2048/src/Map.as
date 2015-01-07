package
{
	import flash.display.Shape;
	import flash.events.Event;
	
	public class Map extends Shape {
		
		public function Map() {
			this.graphics.beginFill(0xbbada1, 1);
			this.graphics.drawRoundRect(0, 0, 500, 500, 20);
			this.graphics.endFill();
		}
	}
}