package
{
	import flash.display.Sprite;
	import flash.text.TextField;
	
	
	public class DisplayBox extends Sprite {
		private var display:TextField;
		private var score:TextField;
		
		public function DisplayBox(width:int, height:int , color:uint ,
								   Display:TextField, Score:TextField = null) {
			this.graphics.beginFill(color);
			this.graphics.drawRoundRect(0, 0, width, height, 5);
			this.graphics.endFill();
			display = Display;
			score = Score;	
		
			this.addChild(display);
			
			if(null != Score)
				this.addChild(score);
		}
		
		public function updateName(str:String):void {
			if(null == score)
				return ;
			score.text = str;
			score.width = score.textWidth + 5;
			score.height = score.textHeight + 5;
			
			score.x = (100 - score.width) / 2;
		}
	}
}