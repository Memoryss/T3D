#ifndef __SOFTRENDERER_H__
#define __SOFTRENDERER_H__

namespace T3D {

	class SoftRenderer
	{
	public:
		SoftRenderer();
		~SoftRenderer();

		bool InitRenderer(int width, int height);
		bool StopRender();

		void 

		//‰÷»æ
		void DrawLine();
		void DrawPrimitive();
	};

}

#endif
