package com.example.smart_eggplant;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.view.View;

public class BatteryView extends View {
    private Paint paint;
    private RectF rectF;
    private float batteryPercentage = 0;
    private Bitmap batteryIcon;

    public BatteryView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    private void init(Context context) {
        paint = new Paint(Paint.ANTI_ALIAS_FLAG);
        rectF = new RectF();
        batteryIcon = BitmapFactory.decodeResource(context.getResources(), R.drawable.robot);
    }



    public void setBatteryPercentage(float percentage) {
        this.batteryPercentage = percentage;
        invalidate();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        int width = getWidth();
        int height = getHeight();
        int padding = 10;
        int strokeWidth = 20;

        // 设置圆环的颜色和宽度
        paint.setStrokeWidth(strokeWidth);
        paint.setStyle(Paint.Style.STROKE);





        // 绘制背景圆环
        paint.setColor(0xFFEEEEEE);
        rectF.set(padding, padding, width - padding, height - padding);
        canvas.drawOval(rectF, paint);


        // 根据电量设置颜色
        if (batteryPercentage < 20) {
            paint.setColor(0xFFFF0000); // 红色
        } else if (batteryPercentage < 80) {
            paint.setColor(0xFFFFA500); // 橙色
        } else {
            paint.setColor(0xFF00FF00); // 绿色
        }

        // 绘制前景圆环表示电量
       // paint.setColor(0xFF76FF03);
        float sweepAngle = 360 * batteryPercentage / 100;
        canvas.drawArc(rectF, -90, sweepAngle, false, paint);


        // 绘制电池图标
        int iconSize = 100;
        canvas.drawBitmap(batteryIcon, (width - iconSize) / 2, (height - iconSize) / 2, null);



        // 绘制文本
        // 根据电量设置颜色
        if (batteryPercentage < 20) {
            paint.setColor(0xFFFF0000); // 红色
        } else if (batteryPercentage < 80) {
            paint.setColor(0xFFFFA500); // 橙色
        } else {
            paint.setColor(0xFF00FF00); // 绿色
        }
        paint.setStyle(Paint.Style.FILL);
        paint.setTextSize(40);
        String text = "剩余电量：" + (int) batteryPercentage + "%";
        float textWidth = paint.measureText(text);
        canvas.drawText(text, (width - textWidth) / 2,  height / 2 + 100,paint); // 调整文本位置到圆环下方
    }
}