package
{
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	public class Text extends TextField {
		public function Text(size:int, str:String, width:int, height:int, 
							 	color:uint, isBold:Boolean = true) {
			super();
			var text_format:TextFormat = new TextFormat();
			text_format.size = size
			text_format.font = "Consolas";
			text_format.bold = isBold;
			text_format.color = color;
			
			this.defaultTextFormat = text_format;
			this.mouseEnabled = false;
			this.text = str;
			this.width = this.textWidth + 5;
			this.height = this.textHeight + 5;
		
			this.x = width;
			this.y = height;
		}
	}
}