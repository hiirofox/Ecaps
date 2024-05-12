#pragma once

#include <JuceHeader.h>

#define M_PI 3.1415926535897932384626

/*
hiirofox
2024/2/15
*/

class L_MODEL_STYLE : public juce::LookAndFeel_V4 //���
{
public:
	//������
	void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const juce::Slider::SliderStyle style, juce::Slider& slider) override
	{

	}
	//��ť
	void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle,
		float rotaryEndAngle, juce::Slider& slider) override
	{
		juce::Path arcPath1, arcPath2;
		float zoomVal = 0.55;//�Ŵ�ϵ��
		arcPath1.addArc(x + width * (1.0 - zoomVal) / 2.0, y + height * (1.0 - zoomVal) / 2.0 - 4, width * zoomVal, height * zoomVal, M_PI / 4 - M_PI, M_PI / 4 - M_PI + sliderPosProportional * M_PI * 1.5, true);
		arcPath2.addArc(x + width * (1.0 - zoomVal) / 2.0, y + height * (1.0 - zoomVal) / 2.0 - 4, width * zoomVal, height * zoomVal, M_PI / 4 - M_PI + sliderPosProportional * M_PI * 1.5, -M_PI / 4 + M_PI, true);
		g.setColour(juce::Colour(0x66, 0x66, 0xCC));
		g.strokePath(arcPath1, juce::PathStrokeType(4.0));//���ƣ�������������߿�
		g.setColour(juce::Colour(0x33, 0x33, 0x66));
		g.strokePath(arcPath2, juce::PathStrokeType(4.0));

		g.setColour(juce::Colour(0x22, 0xff, 0x22));//����ɫ����
		float rotx = -sin(M_PI / 4 + sliderPosProportional * M_PI * 1.5), roty = cos(M_PI / 4 + sliderPosProportional * M_PI * 1.5);
		g.drawLine(x + width / 2 + rotx * 11 * zoomVal * 2.0,
			y + height / 2 + roty * 11 * zoomVal * 2.0 - 4,
			x + width / 2 + rotx * 17 * zoomVal * 2.0,
			y + height / 2 + roty * 17 * zoomVal * 2.0 - 4, 4.0);
	}
	//��ť
	void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)override//���ư�ť����
	{
		if (shouldDrawButtonAsHighlighted) g.setColour(juce::Colour(0x66, 0x66, 0xCC));
		else g.setColour(juce::Colour(0x33, 0x33, 0x66));

		juce::Rectangle<int> rect = button.getBounds();
		int x = rect.getX(), y = rect.getY(), w = rect.getWidth(), h = rect.getHeight();
		g.drawLine(x, y, x + w, y, 4);
		g.drawLine(x, y, x, y + h, 4);
		g.drawLine(x + w, y + h, x + w, y, 4);
		g.drawLine(x + w, y + h, x, y + h, 4);

	}
	void drawButtonText(juce::Graphics& g, juce::TextButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)//���ư�ť���������
	{

	}
	//���ذ�ť
	void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
	{
		juce::Rectangle<int> rect = button.getBounds();
		int x = rect.getX(), y = rect.getY(), w = rect.getWidth(), h = rect.getHeight();//��ȡ��ť�ߴ�

		if (shouldDrawButtonAsDown || button.getToggleState())//�������
		{
			g.setColour(juce::Colour(0x33, 0x33, 0x66));
			g.fillRect(x, y, w, h);//��������
		}
		else if (shouldDrawButtonAsHighlighted)//�����꿿��
		{
			g.setColour(juce::Colour(0x22, 0x22, 0x44));
			g.fillRect(x, y, w, h);//��������
		}//���򲻻�����

		g.setColour(juce::Colour(0x77, 0x77, 0xEE));
		g.drawLine(x, y, x + w, y, 4);//����
		g.drawLine(x, y, x, y + h, 4);
		g.drawLine(x + w, y + h, x + w, y, 4);
		g.drawLine(x + w, y + h, x, y + h, 4);

		//��������
		g.setColour(juce::Colour(0xff, 0xff, 0xff));
		juce::String name = button.getButtonText();
		g.setFont(juce::Font("FIXEDSYS", 15.0, 0));
		g.drawText(name, x, y, w, h, juce::Justification::centred);
	}
	//�����˵�
	void drawComboBox(juce::Graphics& g,
		int width, int height,
		bool isButtonDown,
		int buttonX, int buttonY, int buttonWidth, int buttonHeight,
		juce::ComboBox& box) override//�������
	{
		int x = box.getX(), y = box.getY(), w = box.getWidth(), h = box.getHeight();
		if (isButtonDown)//�����꿿��
		{
			g.setColour(juce::Colour(0x22, 0x22, 0x44));
			g.fillRect(x + 2, y, w - 4, h);//��������
		}

		g.setColour(juce::Colour(0x77, 0x77, 0xEE));
		g.drawLine(x, y, x + w, y, 4);//����
		g.drawLine(x, y, x, y + h, 4);
		g.drawLine(x + w, y + h, x + w, y, 4);
		g.drawLine(x + w, y + h, x, y + h, 4);

		/*
		g.setColour(juce::Colour(0x77, 0xff, 0x77));
		juce::String name = box.getText();
		g.setFont(juce::Font("FIXEDSYS", 15.0, 0));
		g.drawText(name, x + 8, y, w - 8, h, juce::Justification::centredLeft);
		*/
	}
	void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
		const bool isSeparator, const bool isActive,
		const bool isHighlighted, const bool isTicked,
		const bool hasSubMenu, const juce::String& text,
		const juce::String& shortcutKeyText,
		const juce::Drawable* icon, const juce::Colour* textColour) override//���˵��������������
	{
		int x = area.getX(), y = area.getY(), w = area.getWidth(), h = area.getHeight();
		if (isTicked)//�������
		{
			g.setColour(juce::Colour(0x44, 0x44, 0x88));
			g.fillRect(x + 2, y, w - 4, h);//��������
		}
		else if (isHighlighted)//�����꿿��
		{
			g.setColour(juce::Colour(0x22, 0x22, 0x44));
			g.fillRect(x + 2, y, w - 4, h);//��������
		}

		g.setColour(juce::Colour(0x77, 0xff, 0x77));
		g.setFont(juce::Font("FIXEDSYS", 15.0, 0));
		g.drawText(text, x + 8, y, w - 8, h, juce::Justification::centredLeft);
	}
	void drawPopupMenuBackground(juce::Graphics& g, int width, int height) override//���˵����
	{
		g.fillAll(juce::Colour(0x11, 0x11, 0x22));//�ڵ�
		g.setColour(juce::Colour(0x44, 0x44, 0x88));
		g.drawLine(0, 0, width, 0, 4);
		g.drawLine(0, 0, 0, height, 4);
		g.drawLine(width, height, width, 0, 4);
		g.drawLine(width, height, 0, height, 4);
	}
private:
};


class Custom1_Slider : public juce::Slider//���¾��������ָ���Slider
{
public:
protected:
	void mouseDown(const juce::MouseEvent& event) override
	{
		lastMousePosition = event.source.getScreenPosition();
		setMouseCursor(juce::MouseCursor::NoCursor);
		juce::Slider::mouseDown(event);
	}
	void mouseUp(const juce::MouseEvent& event) override
	{
		juce::Desktop::getInstance().getMainMouseSource().setScreenPosition(lastMousePosition);
		setMouseCursor(juce::MouseCursor::NormalCursor);
		juce::Slider::mouseUp(event);
	}
private:
	juce::Point<float> lastMousePosition;
};
class LMKnob :public juce::Component//��ť��
{
public:
	LMKnob() :slider(), label()
	{
		slider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
		slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		L_MODEL_STYLE_LOOKANDFEEL = std::make_unique<L_MODEL_STYLE>();
		slider.setLookAndFeel(L_MODEL_STYLE_LOOKANDFEEL.get());//Ӧ��l-model���
		label.setJustificationType(juce::Justification::centredTop);
		label.setFont(juce::Font("FIXEDSYS", 15.0, 0));
		label.setMinimumHorizontalScale(1.0);//����������
		label.setColour(juce::Label::textColourId, juce::Colour(0x77, 0xff, 0x77));
		label.setFont(label.getFont().withStyle(juce::Font::bold));//���ô���
		/*
		slider.onValueChange = [this]
		{
			this->repaint(-64, -64, 128, 128);
		};
		slider.setInterceptsMouseClicks(true, true);//ʹ��slider������������Ҳ�ܽ�������¼�
		*/
		setPaintingIsUnclipped(true);//����ޱ߽�
		setOpaque(false);//�����ɫ����͸��

		addAndMakeVisible(slider);
		addAndMakeVisible(label);
	}
	~LMKnob()
	{
		slider.setLookAndFeel(nullptr);
		ParamLinker = nullptr;
	}
	void paint(juce::Graphics& g) override
	{
		/*
		auto centreX = getWidth() / 2;//��������ԭ��
		auto centreY = getHeight() / 2;
		g.setOrigin(-centreX, -centreY);*/

		/*
		g.setColour(juce::Colour(0x00, 0xff, 0x00));//��ײ��
		g.drawLine(0, 0, 64, 0);
		g.drawLine(0, 0, 0, 80);
		g.drawLine(64, 80, 64, 0);
		g.drawLine(64, 80, 0, 80);*/
	}
	juce::Slider& getSlider()
	{
		return slider;
	}
	void ParamLink(juce::AudioProcessorValueTreeState& stateToUse, const juce::String& parameterID)
	{
		ParamLinker = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToUse, parameterID, slider);
	}
	void setText(const juce::String& KnobText)
	{
		label.setText(KnobText, juce::dontSendNotification);
		text = KnobText;

	}
	void resized() override {
		slider.setBounds(32 - 56 / 2, 32 - 56 / 2, 56, 56);
		label.setBounds(-32, 48 - 4, 64 + 64, 16);
	}
	void setPos(int x, int y)//����setBounds�������ٴ򼸸���
	{
		setBounds(x - 32, y - 32, 64, 64);
	}
private:
	std::unique_ptr<L_MODEL_STYLE> L_MODEL_STYLE_LOOKANDFEEL;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ParamLinker;
	//juce::Slider slider;
	Custom1_Slider slider;
	juce::Label label;
	juce::String text;
};

class LMButton : public juce::Component, public juce::Button::Listener//��ť��
{
public:
	LMButton()
	{
		// ���ð�ť����
		button.setButtonText(name);
		button.addListener(this); // ע��������Դ���ť���

		L_MODEL_STYLE_LOOKANDFEEL = std::make_unique<L_MODEL_STYLE>();
		button.setLookAndFeel(L_MODEL_STYLE_LOOKANDFEEL.get());//Ӧ��l-model���

		setPaintingIsUnclipped(true);//����ޱ߽�
		setOpaque(false);//�����ɫ����͸��

		addAndMakeVisible(button);
	}
	~LMButton()
	{
		button.setLookAndFeel(nullptr);
	}
	void setName(juce::String ButtonName)
	{
		name = ButtonName;
		button.setButtonText(name);
	}
	void resized() override
	{
		// ���ð�ť��λ�úʹ�С
		button.setBounds(0, 0, Width, 24);
	}
	void setPos(int x, int y)//���setBounds
	{
		setBounds(x - Width / 2, y - 12, Width, 24);
	}
	void setButtonWidth(int ButtonWidth)
	{
		Width = ButtonWidth;
		button.setBounds(0, 0, Width, 24);
		setBounds(getX(), getY(), Width, 24);
		repaint();
	}
	void buttonClicked(juce::Button* clicked) override
	{
		if (clicked == &button)
		{
			//�������...
			if (button.isDown())
			{
				if (state != NULL)
					*state = 1;
			}
			else
			{
				if (state != NULL)
					*state = 0;
			}
		}
	}
	void SetStateValuePtr(int* StateValue)
	{
		state = StateValue;
	}
private:
	std::unique_ptr<L_MODEL_STYLE> L_MODEL_STYLE_LOOKANDFEEL;
	//juce::TextButton button;//����ť
	juce::ToggleButton button;//����
	juce::String name;
	int* state = NULL;
	int Width = 64;
};

class LMCombox : public juce::Component, private juce::ComboBox::Listener//�����˵���
{
public:
	LMCombox()
	{
		comboBox.addListener(this);
		L_MODEL_STYLE_LOOKANDFEEL = std::make_unique<L_MODEL_STYLE>();
		comboBox.setLookAndFeel(L_MODEL_STYLE_LOOKANDFEEL.get());//Ӧ��l-model���
		addAndMakeVisible(comboBox);
	}
	~LMCombox()
	{
		comboBox.setLookAndFeel(nullptr);
	}
	void addItem(juce::String name, int ID)
	{
		comboBox.addItem(name, ID);
	}
	void setSelectedID(int ID)
	{
		comboBox.setSelectedId(ID);
	}

	void setPos(int x, int y)
	{
		setBounds(x - Width / 2, y - 12, Width, 24);
	}
	void setComboxWidth(int ComboxWidth)
	{
		Width = ComboxWidth;
		comboBox.setBounds(0, 0, Width, 24);
		setBounds(getX(), getY(), Width, 24);
	}
	void resized() override
	{
		// ����ComboBox��λ�úʹ�С
		comboBox.setBounds(0, 0, Width, 24);
	}

private:
	std::unique_ptr<L_MODEL_STYLE> L_MODEL_STYLE_LOOKANDFEEL;
	juce::ComboBox comboBox;
	int Width = 64;

	// ComboBoxѡ��ı�ʱ�Ļص�����
	void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override
	{
		if (comboBoxThatHasChanged == &comboBox)
		{
		}
	}

};