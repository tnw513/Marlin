#ifndef SCREEN_DIALOG_H
#define SCREEN_DIALOG_H

#include "Screen.h"
#include "Functor.h"

namespace screen
{
	template <typename R, typename... Args>
		class ScreenDialog : public Screen , public Functor<R, Args ...>
	{
		public:
			ScreenDialog(const char * title, const char * box, typename Functor<R, Args...>::FuncPtr fptr = do_nothing);
			virtual ~ScreenDialog();

			Screen & press(Screen * parent_view);
			void draw();

		private:
			const char * m_box;
	};

	template <typename R, typename... Args>
	ScreenDialog<R, Args...>::ScreenDialog(const char * title, const char * box, typename Functor<R, Args...>::FuncPtr fptr)
		: Screen(title, DIALOG)
		, Functor<R, Args...>(fptr)
		, m_box(box)
	{ }

	template <typename R, typename... Args>
	ScreenDialog<R, Args...>::~ScreenDialog()
	{ }

	template <typename R, typename... Args>
	Screen & ScreenDialog<R, Args...>::press(Screen * parent_view)
	{
		this->action();
		return * m_next_screen;
	}

	template <typename R, typename... Args>
	void ScreenDialog<R, Args...>::draw()
	{
		SERIAL_ECHO("DRAW: ");
		SERIAL_ECHOLN(m_title);

		painter.firstPage();
		do
		{
			painter.title(m_title);
			painter.box(m_box);

		} while ( painter.nextPage() );
	}
}


#endif //SCREEN_DIALOG_H