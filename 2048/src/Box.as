package
{
	import flash.display.Sprite;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	public class Box extends Sprite
	{
		private var val		:int;
		
		public function getVal() {
			return this.val;
		}
		
		public function Box(num:int = 0, length:int = GameWorld.square_length)
		{
			this.val = num;
			var color:Array = new Array(0xcdc1b5, 0xefe5db, 0xede1c9,
				0xf3b178, 0xf59562, 0xf77c5e, 0xf75e3a, 0xedcf72,
				0xedcd60, 0xedc950, 0xedc53e, 0xeec032, 0xff3c3e,
				0xfe1e1e);
			if(0 == num)
				this.graphics.beginFill(color[0], 0.5);
			else
				this.graphics.beginFill(color[num]);
			this.graphics.drawRoundRect(0, 0, length, length, 10);
				
			if(0 == num)
				return ;
			
			var result:int = 1;
			for (var i :int = 0; i < num; i++)
				result *= 2;
			var m_text : TextField = new TextField();
			
			var tFormat: TextFormat = new TextFormat();

			if(num > 2)
				tFormat.color = 0xf9f5f3;
			else 
				tFormat.color = 0x766e64;
			tFormat.font = "Consolas";
			tFormat.bold = true;
			
			if(result > 999)
				tFormat.size = 45;
			else if(result > 99)
				tFormat.size = 55;
			else 
				tFormat.size = 70;
			
			m_text.defaultTextFormat = tFormat;
			m_text.mouseEnabled = false;
		
			m_text.text = result.toString();
		
			m_text.width = m_text.textWidth + 5;
			m_text.height = m_text.textHeight + 5;
			
			m_text.x = (length - m_text.width)/2;
			m_text.y = (length - m_text.height)/2;
			this.addChild(m_text);
		}
	}
}