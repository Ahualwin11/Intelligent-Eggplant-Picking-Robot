package com.example.smart_eggplant;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.PagerAdapter;
import androidx.viewpager.widget.ViewPager;

import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;


import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;

import com.github.mikephil.charting.charts.PieChart;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.data.PieData;
import com.github.mikephil.charting.data.PieDataSet;
import com.github.mikephil.charting.data.PieEntry;
import com.github.mikephil.charting.formatter.IndexAxisValueFormatter;
import com.github.mikephil.charting.utils.ColorTemplate;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;


import com.github.mikephil.charting.charts.RadarChart;
import com.github.mikephil.charting.data.RadarData;
import com.github.mikephil.charting.data.RadarDataSet;
import com.github.mikephil.charting.data.RadarEntry;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.components.YAxis;

import com.github.mikephil.charting.formatter.ValueFormatter;
import com.google.android.material.slider.Slider;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Locale;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.view.View;

import android.Manifest;
import android.content.pm.PackageManager;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CaptureRequest;
import android.os.Bundle;
import android.view.Surface;
import android.view.TextureView;
import android.view.TextureView.SurfaceTextureListener;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {
    private RadioGroup mRadioGroup;
    private ViewPager mViewPager;
    private RadioButton tab1, tab2, tab3;  //四个单选按钮
    private TableLayout table; //表
    private String eggplant_quantity_data = "0个";
    private String data = "1-长茄-"+eggplant_quantity_data+"-100%-A棚-24/7/18#2-紫茄-3个-100%-B棚-24/7/17#3-长茄-3个-100%-C棚-24/7/16#4-紫茄-5个-100%-B棚-24/7/15#5-圆茄-4个-100%-C棚-24/7/14";
    private String[] records;
    private ArrayList<String> number = new ArrayList<>();
    private ArrayList<String> type = new ArrayList<>();
    private ArrayList<String> box = new ArrayList<>();
    private ArrayList<String> good = new ArrayList<>();
    private ArrayList<String> here = new ArrayList<>();
    private ArrayList<String> time = new ArrayList<>();
    private List<View> mViews;   //存放视图
    private int position_1;

    private int position_2;
    private int position_3;
    private int position_4;
    private PieChart pieChart;
    private LineChart chart;

    private TextureView textureView;
    private CameraDevice cameraDevice;
    private CameraCaptureSession captureSession;
    private CaptureRequest.Builder captureRequestBuilder;


    //页面四 选项框
    private Spinner spinner_type;
    private String spinner_type_data;
    private Spinner spinner_time;
    private String spinner_time_data;
    private Button button_search;
    private Button egg_msg;


    //服务器
    private Socket socket;
    private OutputStream outputStream;
    private InputStream inputStream;
    MainActivity.MyHandler myHandler;  //使用Handler更新控件
    private boolean RECV_flag;
    private TextView textViewRec;
    private MainActivity mActivity;
    private String content_ip = "192.168.1.155";
    private String content_port = "8888";
    private EditText editTextSend;
    private Button button_send;
    private Button button_link;
    private EditText port;
    private EditText ip_data;


    //电量
    private BatteryView batteryView;
    private ToggleButton toggleButtonLight;
    private Slider seekBarBrightness;
    //机器人传感器信息


    private String temperature = "21.3℃";
    private String humidity = "88.7%";
    private String lightIntensity = "0.85lx";
    private String ultravioletIntensity = "4w/m²";

    private String picking_efficiency_of_eggplant_data = "0个/h";
    private float power = 95;

    //启动
    private TextView stop_start;
    private TextView greenhouse_temperature;
    private TextView greenhouse_humidity;
    private TextView light_intensity;
    private TextView ultraviolet_intensity;

    private TextView picking_efficiency_of_eggplant;
    private TextView eggplant_quantity;

    //下拉选项框
    private Spinner eggplant_greenhouse_classification;
    private Spinner robot_number;
    private TableLayout tableLayout;

    //日期
    private TextView date_year_month_day_week ;
    private TextView system_refresh_time ;
    private SimpleDateFormat sdf = new SimpleDateFormat("yyyy年MM月dd日 EEEE", Locale.getDefault());
    private String currentDate = sdf.format(new Date());


    //活动页面的入口函数
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getSupportActionBar().hide(); // 隐藏标题栏
        setContentView(R.layout.activity_main_ui);

        mActivity = this;  // 初始化mActivity
        myHandler = new MainActivity.MyHandler();  // 使用handler更新控件
        initView();//初始化数据

        //底部导航栏
        mRadioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, int i) {
                if (i == R.id.main_home) {
                    mViewPager.setCurrentItem(0);
                }
                if (i == R.id.main_scene) {
                    mViewPager.setCurrentItem(1);
                }
                if (i == R.id.main_my) {
                    mViewPager.setCurrentItem(2);
                }
            }
        });

        //链接服务器开启接收
        new Thread(new Runnable() {
            @Override
            public void run() {
                Message msg = myHandler.obtainMessage();//从消息队列拉取个消息变量
                try {
                    socket = new Socket(content_ip, Integer.parseInt(content_port));
                    if (socket.isConnected()) {
//                                    SocketSingleton.setSocketInstance(socket);
                        msg.what = 1;//设置消息变量的 what 变量值 为1 按钮变成断开 显示连接成功
                        Log.i("Tag", "连接成功");
                        Log.i("IP", content_ip);
                        Log.i("Port", content_port);
                        inputStream = socket.getInputStream();
                        outputStream = socket.getOutputStream();
                        sendText("app");  // 第一次连接，发送用户信息
                        RECV_flag = true;
                        Recv();
                    } else {
                        msg.what = 0;//设置消息变量的 what 变量值 为0
                        Log.i("Tag", "断开链接");
                        Log.i("IP", content_ip);
                        Log.i("Port", content_port);
                    }
                } catch (Exception e) {
                    msg.what = 3;//设置消息变量的 what 变量值 为0
                    Log.i("Tag", "服务器异常");
                    Log.i("IP", content_ip);
                    Log.i("Port", content_port);
                    e.printStackTrace();
//
                }
                myHandler.sendMessage(msg);//插入消息队列
            }
        }).start();
        //更新表格数据



    }

    //页面数据的初始化
    private void initView() {

        mViewPager = findViewById(R.id.viewpager);
        mRadioGroup = findViewById(R.id.rg_tab);
        tab1 = findViewById(R.id.main_home);
        tab2 = findViewById(R.id.main_scene);
        tab3 = findViewById(R.id.main_my);

        mViews = new ArrayList<View>();//加载，添加视图
        mViews.add(LayoutInflater.from(this).inflate(R.layout.activity_main_one, null));
        mViews.add(LayoutInflater.from(this).inflate(R.layout.activity_mian_tow, null));
        mViews.add(LayoutInflater.from(this).inflate(R.layout.me, null));
        mViews.add(LayoutInflater.from(this).inflate(R.layout.activity_mian_msg, null));
        mViews.add(LayoutInflater.from(this).inflate(R.layout.activity_mian_connect, null));


        MyViewPagerAdapter adapter = new MyViewPagerAdapter();
        mViewPager.setAdapter(adapter);
        adapter.setAccessFindPage(false);


        //对viewpager监听，让分页和底部图标保持一起滑动
        mViewPager.setOnPageChangeListener(new ViewPager.OnPageChangeListener() {
            @Override
            public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {

            }

            @Override   //让viewpager滑动的时候，下面的图标跟着变动
            public void onPageSelected(int position) {
                switch (position) {
                    case 0:
                        tab1.setChecked(true);
                        tab2.setChecked(false);
                        tab3.setChecked(false);
                        break;
                    case 1:
                        tab1.setChecked(false);
                        tab2.setChecked(true);
                        tab3.setChecked(false);
                        break;
                    case 2:
                        tab1.setChecked(false);
                        tab2.setChecked(false);
                        tab3.setChecked(true);
                        break;
                }
            }

            @Override
            public void onPageScrollStateChanged(int state) {
            }
        });

        initView_1_home();
        initView_2_scene();
        initView_3_my();
        initView_4_msg();
        initView_5_msg();

    }

    private void initView_1_home() {
        position_1 = 0;
        pieChart = mViews.get(position_1).findViewById(R.id.pie_chart);
        chart = mViews.get(position_1).findViewById(R.id.chart);
        textureView = mViews.get(position_1).findViewById(R.id.camera_preview);
        textViewRec = mViews.get(position_1).findViewById(R.id.textView_Rec);
        editTextSend = mViews.get(position_1).findViewById(R.id.editTextSend);
        eggplant_greenhouse_classification = mViews.get(position_1).findViewById(R.id.eggplant_greenhouse_classification);
        date_year_month_day_week = mViews.get(position_1).findViewById(R.id.date_year_month_day_week);

        date_year_month_day_week.setText(currentDate);


        List<PieEntry> pieEntries = new ArrayList<>();
        pieEntries.add(new PieEntry(18.5f, "在线"));
        pieEntries.add(new PieEntry(26.7f, "离线"));
        pieEntries.add(new PieEntry(24.0f, "故障"));
        pieEntries.add(new PieEntry(30.8f, "维修"));
        PieDataSet pieSet = new PieDataSet(pieEntries, "");
        pieSet.setColors(ColorTemplate.MATERIAL_COLORS);
        PieData pieData = new PieData(pieSet);
        pieChart.setData(pieData);
        pieChart.invalidate();


        eggplant_greenhouse_classification.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                updateLineChart(position);  // 根据选择更新折线图
                Toast.makeText(mActivity, "大棚信息已更新", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });


        // 初始化折线图
        updateLineChart(0);  // 默认显示第一项数据

        //视频流
        if (textureView.isAvailable()) {
            openCamera();
        } else {
            textureView.setSurfaceTextureListener(new SurfaceTextureListener() {
                @Override
                public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
                    openCamera();
                }

                @Override
                public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
                }

                @Override
                public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
                    return false;
                }

                @Override
                public void onSurfaceTextureUpdated(SurfaceTexture surface) {
                }
            });
        }


    }

    // 根据大棚类型更新折线图数据
    private void updateLineChart(int greenhouseIndex) {


        List<Entry> entries = new ArrayList<>();
        if (greenhouseIndex == 0) {  // 长茄子大棚
            entries.add(new Entry(0, 30));
            entries.add(new Entry(1, 80));
            entries.add(new Entry(2, 11));
            entries.add(new Entry(3, 50));
            entries.add(new Entry(4, 90));
            entries.add(new Entry(5, 100));
            entries.add(new Entry(6, 70));
            entries.add(new Entry(7, 60));
            entries.add(new Entry(8, 50));
            entries.add(new Entry(9, 40));
        } else if (greenhouseIndex == 1) {  // 短茄子大棚
            entries.add(new Entry(0, 80));
            entries.add(new Entry(1, 88));
            entries.add(new Entry(2, 60));
            entries.add(new Entry(3, 50));
            entries.add(new Entry(4, 90));
            entries.add(new Entry(5, 100));
            entries.add(new Entry(6, 70));
            entries.add(new Entry(7, 50));
            entries.add(new Entry(8, 50));
            entries.add(new Entry(9, 70));
        } else if (greenhouseIndex == 2) {  // 圆子茄大棚
            entries.add(new Entry(0, 55));
            entries.add(new Entry(1, 80));
            entries.add(new Entry(2, 33));
            entries.add(new Entry(3, 50));
            entries.add(new Entry(4, 55));
            entries.add(new Entry(5, 100));
            entries.add(new Entry(6, 70));
            entries.add(new Entry(7, 11));
            entries.add(new Entry(8, 50));
            entries.add(new Entry(9, 99));
        }


        LineDataSet dataSet = new LineDataSet(entries, "大棚数据");
        dataSet.setMode(LineDataSet.Mode.CUBIC_BEZIER);
        dataSet.setCubicIntensity(0.2f);
        //   dataSet.setColor(Color.GREEN);
        dataSet.setColor(ColorTemplate.COLORFUL_COLORS[greenhouseIndex]);
        dataSet.setValueTextColor(Color.BLACK);
        dataSet.setValueTextSize(12f);

        dataSet.setLineWidth(2f);
        dataSet.setDrawFilled(true);
        dataSet.setFillColor(Color.GREEN);
        dataSet.setDrawValues(false);
        LineData lineData = new LineData(dataSet);
        chart.setData(lineData);

        XAxis xAxis = chart.getXAxis();
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setValueFormatter(new DateAxisValueFormatter());
        xAxis.setGranularity(1f);  // minimum axis-step (interval) is 1

        chart.invalidate();

    }

    private void initView_2_scene() {
        position_2 = 1;


        stop_start = mViews.get(position_2).findViewById(R.id.stop_start);
        greenhouse_temperature = mViews.get(position_2).findViewById(R.id.greenhouse_temperature);
        greenhouse_humidity = mViews.get(position_2).findViewById(R.id.greenhouse_humidity);
        light_intensity = mViews.get(position_2).findViewById(R.id.light_intensity);
        ultraviolet_intensity = mViews.get(position_2).findViewById(R.id.ultraviolet_intensity);
        picking_efficiency_of_eggplant = mViews.get(position_2).findViewById(R.id.picking_efficiency_of_eggplant);
        eggplant_quantity = mViews.get(position_2).findViewById(R.id.eggplant_quantity);
        toggleButtonLight = mViews.get(position_2).findViewById(R.id.toggleButtonLight);
        batteryView = mViews.get(position_2).findViewById(R.id.batteryView);
        seekBarBrightness = mViews.get(position_2).findViewById(R.id.seekBarBrightness);
        robot_number = mViews.get(position_2).findViewById(R.id.robot_number);
        system_refresh_time = mViews.get(position_2).findViewById(R.id.system_refresh_time);

        system_refresh_time.setText("刷新时间"+new SimpleDateFormat("HH:mm", Locale.getDefault()).format(new Date())); // 更新系统刷新时间




        seekBarBrightness.setValue(power);  // 设置默认值
        batteryView.setBatteryPercentage(power);

        toggleButtonLight.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

                if (isChecked) {

                    if (socket != null && socket.isConnected()) {
                        stop_start.setText("暂停");
                        sendText("r");
                        Toast.makeText(mActivity, "设备启动成功", Toast.LENGTH_SHORT).show();
                    }else {
                        Toast.makeText(mActivity, "请先连接服务器", Toast.LENGTH_SHORT).show();
                        toggleButtonLight.setChecked(false);
                        Message msg = myHandler.obtainMessage();//从消息队列拉取个消息变量
                        msg.what = 0;//设置消息变量的 what 变量值 为0
                        Log.i("Tag", "断开链接");
                        Log.i("IP", content_ip);
                        Log.i("Port", content_port);
                    }
                } else {
                    if (socket != null && socket.isConnected()) {
                        stop_start.setText("启动");
                        sendText("t");
                        Toast.makeText(mActivity, "设备暂停成功", Toast.LENGTH_SHORT).show();
                    }else {
                        Toast.makeText(mActivity, "请先连接服务器", Toast.LENGTH_SHORT).show();
                        toggleButtonLight.setChecked(true);
                        Message msg = myHandler.obtainMessage();//从消息队列拉取个消息变量
                        msg.what = 0;//设置消息变量的 what 变量值 为0
                        Log.i("Tag", "断开链接");
                        Log.i("IP", content_ip);
                        Log.i("Port", content_port);
                    }

                }

            }
        });
        //滑动条监听
        seekBarBrightness.addOnChangeListener(new Slider.OnChangeListener() {
            @Override
            public void onValueChange(@NonNull Slider slider, float value, boolean fromUser) {
                batteryView.setBatteryPercentage(value);

            }
        });
        robot_number.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                update_robot(position);  // 根据选择更新折线图
                system_refresh_time.setText("刷新时间"+new SimpleDateFormat("HH:mm", Locale.getDefault()).format(new Date())); // 更新系统刷新时间
                Toast.makeText(mActivity, "机器人已切换", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });


    }

    // 根据大棚类型更新折线图数据
    private void update_robot(int robot_number) {


        if (robot_number == 0) {  // 1号机器人传感器

            //power = 95;
            greenhouse_temperature.setText(temperature);
            greenhouse_humidity.setText(humidity);
            light_intensity.setText(lightIntensity);
            ultraviolet_intensity.setText(ultravioletIntensity);
            picking_efficiency_of_eggplant.setText(picking_efficiency_of_eggplant_data);
            eggplant_quantity.setText(eggplant_quantity_data);
            seekBarBrightness.setValue(power);  // 设置默认值
            batteryView.setBatteryPercentage(power);

        } else if (robot_number == 1) {  // 2号机器人传感器
            power = 70;
            greenhouse_temperature.setText("25.3℃");
            greenhouse_humidity.setText("96.7%");
            light_intensity.setText("0.53lx");
            ultraviolet_intensity.setText("5w/m²");
            picking_efficiency_of_eggplant.setText("10个");
            eggplant_quantity.setText("8个/h");
            seekBarBrightness.setValue(power);  // 设置默认值
            batteryView.setBatteryPercentage(power);

        } else if (robot_number == 2) {  // 3号机器人传感器
            power = 10;
            greenhouse_temperature.setText("29.3℃");
            greenhouse_humidity.setText("79.7%");
            light_intensity.setText("0.93lx");
            ultraviolet_intensity.setText("7w/m²");
            picking_efficiency_of_eggplant.setText("25个");
            eggplant_quantity.setText("9个/h");
            seekBarBrightness.setValue(power);  // 设置默认值
            batteryView.setBatteryPercentage(power);
        }

    }

    private void initView_3_my() {

    }

    private void initView_4_msg() {

        parseData();


        position_3 = 3;

        spinner_type = mViews.get(position_3).findViewById(R.id.spinner_type);
        spinner_time = mViews.get(position_3).findViewById(R.id.spinner_time);
        button_search = mViews.get(position_3).findViewById(R.id.button_search);
        egg_msg = mViews.get(position_3).findViewById(R.id.egg_msg);
        tableLayout = mViews.get(position_3).findViewById(R.id.tableLayout);


        // 初始化 spinner_type
        ArrayAdapter<CharSequence> typeAdapter = ArrayAdapter.createFromResource(this,
                R.array.type, android.R.layout.simple_spinner_item);
        typeAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner_type.setAdapter(typeAdapter);

        // 解析时间数据并初始化 spinner_time
        updateSpinnerTimeData();

        spinner_type.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                spinner_type_data = parent.getItemAtPosition(position).toString();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });
        spinner_time.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                spinner_time_data = parent.getItemAtPosition(position).toString();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });


    }

    private void initView_5_msg() {


        position_4 = 4;

        textViewRec = mViews.get(position_4).findViewById(R.id.textView_Rec);
        editTextSend = mViews.get(position_4).findViewById(R.id.editTextSend);
        button_send = mViews.get(position_4).findViewById(R.id.button_send);
        button_link = mViews.get(position_4).findViewById(R.id.button_link);

        ip_data = mViews.get(position_4).findViewById(R.id.ip);
        port = mViews.get(position_4).findViewById(R.id.port);


    }

    //ViewPager适配器
    private class MyViewPagerAdapter extends PagerAdapter {
        private boolean accessFindPage = false;  // 控制是否可以访问 find 页面

        public void setAccessFindPage(boolean access) {
            accessFindPage = access;
            notifyDataSetChanged();  // 通知数据变化，重新加载视图
        }

        @Override
        public int getCount() {
            // 如果 accessFindPage 为 true，则返回所有页面，否则不包括最后一个 find 页面
            return accessFindPage ? mViews.size() : mViews.size() - 1;
        }


        @Override
        public boolean isViewFromObject(@NonNull View view, @NonNull Object object) {
            return view == object;
        }

        @Override
        public void destroyItem(@NonNull ViewGroup container, int position, @NonNull Object object) {
            container.removeView(mViews.get(position));
        }

        @NonNull
        @Override
        public Object instantiateItem(@NonNull ViewGroup container, int position) {

            //            container.addView(mViews.get(position));
//            return mViews.get(position);
            View view = mViews.get(position);
            container.addView(view);
            // 在这里设置按钮的点击事件
            if (position == 0) {  // 假设联系人页面是第二个页面
                initialize_the_listen_button_1(view);
            }
            if (position == 1) {  // 假设联系人页面是第二个页面
//                initialize_the_listen_button_1(view);
                initialize_the_listen_button_2(view);
            }
            if (position == 2) {  // 假设联系人页面是第二个页面
                initialize_the_listen_button_3(view);
            }
            if (position == 3) {
                initialize_the_listen_button_4(view);
            }
            if (position == 4) {
                initialize_the_listen_button_5(view);
            }
            return view;
        }


        public void initialize_the_listen_button_1(View view) {


        }

        public void initialize_the_listen_button_2(View view) {


        }

        public void initialize_the_listen_button_3(View view) {
            ImageView about_us = view.findViewById(R.id.about_us);
            about_us.setOnClickListener(v -> handleButtonClick_3(v));

            ImageView message_center = view.findViewById(R.id.message_center);
            message_center.setOnClickListener(v -> handleButtonClick_3(v));

            ImageView use_help = view.findViewById(R.id.use_help);
            use_help.setOnClickListener(v -> handleButtonClick_3(v));

            ImageView set_button = view.findViewById(R.id.set_button);
            set_button.setOnClickListener(v -> handleButtonClick_3(v));
        }

        public void initialize_the_listen_button_4(View view) {

            button_search.setOnClickListener(v -> handleButtonClick_4(v));
            egg_msg.setOnClickListener(v -> handleButtonClick_4(v));
        }

        public void initialize_the_listen_button_5(View view) {
            // 需要监听的按钮初始化
            button_send.setOnClickListener(v -> handleButtonClick_5(v));
            button_link.setOnClickListener(v -> handleButtonClick_5(v));

        }
    }


    //不同页面的按钮监听
    private void handleButtonClick_1(View v) {


    }

    private void handleButtonClick_3(View v) {
        if (R.id.set_button == v.getId()) {
            mViewPager.setCurrentItem(3);
            updateTable();
        }

        if (R.id.about_us == v.getId()) {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("提示");
            builder.setMessage("即将跳转开发者模式界面...");
            builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    ((MyViewPagerAdapter) mViewPager.getAdapter()).setAccessFindPage(true);
                    mViewPager.setCurrentItem(mViews.size() - 1);
                }
            });
            builder.show();
        }

        if (R.id.use_help == v.getId()) {

            if (socket != null && socket.isConnected()) {
                sendText("app");  // 第一次连接，发送用户信息
                editTextSend.setText("");
                AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setTitle("提示");
                builder.setMessage("使用帮助界面正在搭建...");
                builder.setPositiveButton("期待", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                    }
                });
                builder.show();

            }else {
                Toast.makeText(mActivity, "请先连接服务器", Toast.LENGTH_SHORT).show();
                Message msg = myHandler.obtainMessage();//从消息队列拉取个消息变量
                msg.what = 0;//设置消息变量的 what 变量值 为0
                Log.i("Tag", "断开链接");
                Log.i("IP", content_ip);
                Log.i("Port", content_port);
            }

        }

        if (R.id.message_center == v.getId()) {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("提示");
            builder.setMessage("关于我们界面正在搭建...");
            builder.setPositiveButton("期待", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {

                }
            });

            builder.show();
        }

    }

    private void handleButtonClick_4(View v) {
        if (R.id.button_search == v.getId()) {
            updateTable();
            Toast.makeText(mActivity, "查询成功", Toast.LENGTH_SHORT).show();
        }
        if (R.id.egg_msg == v.getId()) {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("提示");
            builder.setMessage("是否打印该产品一码溯源信息");

            // 创建ImageView并设置资源
            ImageView imageView = new ImageView(MainActivity.this);
            imageView.setImageResource(R.drawable.egg_msg);

            // 设置对话框显示的视图
            builder.setView(imageView);

            builder.setPositiveButton("是", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    // 可以在这里处理用户点击"是"的逻辑
                    Toast.makeText(mActivity, "已发送打印请求", Toast.LENGTH_SHORT).show();
                }
            });
            builder.setNegativeButton("否", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    // 可以在这里处理用户点击"否"的逻辑
                }
            });

            // 显示对话框
            builder.show();
        }
    }

    private void handleButtonClick_5(View v) {
        if (R.id.button_send == v.getId()) {
            String content_send = editTextSend.getText().toString();
            Log.i("Tag", content_send);
            if (content_send.isEmpty()) {
                Toast.makeText(this, "请填写发送信息", Toast.LENGTH_SHORT).show();
            } else {
                // textViewRec.setText(content_send);

                if (socket != null && socket.isConnected()) {
                    sendText(content_send);
                    editTextSend.setText("");
                }else {
                    Toast.makeText(mActivity, "请先连接服务器", Toast.LENGTH_SHORT).show();
                    Message msg = myHandler.obtainMessage();//从消息队列拉取个消息变量
                    msg.what = 0;//设置消息变量的 what 变量值 为0
                    Log.i("Tag", "断开链接");
                    Log.i("IP", content_ip);
                    Log.i("Port", content_port);
                }


            }
        }

        if (R.id.button_link == v.getId()) {
            content_ip = ip_data.getText().toString();

            content_port = port.getText().toString();
            String buttonConnect = button_link.getText().toString();
            if (content_ip.isEmpty() || content_port.isEmpty()) {
                Toast.makeText(this, "请填写完整内容", Toast.LENGTH_SHORT).show();
            } else {
                if ( true) {
                    Log.i("Tag", "尝试连接");
                    Log.i("IP", content_ip);
                    Log.i("Port", content_port);
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            Message msg = myHandler.obtainMessage();//从消息队列拉取个消息变量
                            try {
                                socket = new Socket(content_ip, Integer.parseInt(content_port));
                                if (socket != null && socket.isConnected()) {
//                                    SocketSingleton.setSocketInstance(socket);
                                    msg.what = 1;//设置消息变量的 what 变量值 为1 按钮变成断开 显示连接成功
                                    Log.i("Tag", "连接成功");
                                    Log.i("IP", content_ip);
                                    Log.i("Port", content_port);
                                    inputStream = socket.getInputStream();
                                    outputStream = socket.getOutputStream();
                                    sendText("app"); // 第一次连接，发送用户信息
                                    RECV_flag = true;
                                    Recv();
                                } else {
                                    msg.what = 0;//设置消息变量的 what 变量值 为0
                                    Log.i("Tag", "断开链接");
                                    Log.i("IP", content_ip);
                                    Log.i("Port", content_port);
                                }
                            } catch (Exception e) {
                                msg.what = 3;//设置消息变量的 what 变量值 为0
                                Log.i("Tag", "服务器异常");
                                Log.i("IP", content_ip);
                                Log.i("Port", content_port);
                                e.printStackTrace();

                            }
                            myHandler.sendMessage(msg);//插入消息队列
                        }
                    }).start();
                } else {
                    textViewRec.setText("与服务器断开连接");
                    Log.i("Tag", "断开链接");
                    Log.i("IP", content_ip);
                    Log.i("Port", content_port);
                    try {
                        socket.close();
                    } catch (Exception e) {
                        e.printStackTrace();
                    } //关闭连接
                    try {
                        outputStream.close();
                        inputStream.close();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    button_link.setText("连接");//按钮显示连接
                }
            }
        }

    }

    //数据表
    private void updateTable() {
        tableLayout.removeAllViews();

        // 添加表头
        TableRow header = new TableRow(this);
        header.setBackgroundColor(Color.parseColor("#303F9F"));
        String[] headers = {"编号", "名称", "产量", "合格率", "仓库", "时间"};
        for (String headerText : headers) {
            TextView tv = new TextView(this);
            tv.setText(headerText);
            tv.setTextColor(Color.WHITE);
            tv.setGravity(Gravity.CENTER);
            tv.setPadding(8, 8, 8, 8);
            header.addView(tv);
        }
        tableLayout.addView(header);

        // 添加数据行
        int rowCount = 0; // 新增行计数器
        for (int i = 0; i < number.size(); i++) {
            if ((spinner_type_data.equals("全部") || type.get(i).equals(spinner_type_data)) &&
                    (spinner_time_data.equals("全部") || time.get(i).equals(spinner_time_data))) {
                TableRow row = new TableRow(this);
                row.setBackgroundColor(rowCount % 2 == 0 ? Color.parseColor("#DAE8FC") : Color.parseColor("#ffffff"));
                String[] rowData = {number.get(i), type.get(i), box.get(i), good.get(i), here.get(i), time.get(i)};
                for (String cell : rowData) {
                    TextView tv = new TextView(this);
                    tv.setText(cell);
                    tv.setTextSize(17);
                    tv.setGravity(Gravity.CENTER);
                    tv.setPadding(8, 8, 8, 8);
                    row.addView(tv);
                }
                tableLayout.addView(row);
                rowCount++; // 更新行计数器
            }
        }
    }

    //获取服务器数据 写入数组

    private void parseData() {
        // 清空之前的数据
        number.clear();
        type.clear();
        box.clear();
        good.clear();
        here.clear();
        time.clear();
        records = data.split("#");
        for (String record : records) {
            String[] details = record.split("-");
            number.add(details[0]);
            type.add(details[1]);
            box.add(details[2]);
            good.add(details[3]);
            here.add(details[4]);
            time.add(details[5]);
        }
    }

    //摄像头
    private void openCamera() {
        CameraManager manager = (CameraManager) getSystemService(CAMERA_SERVICE);
        try {
            String cameraId = manager.getCameraIdList()[0];
            if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.CAMERA}, 1);
                return;
            }
            manager.openCamera(cameraId, new CameraDevice.StateCallback() {
                @Override
                public void onOpened(CameraDevice camera) {
                    cameraDevice = camera;
                    createCameraPreviewSession();
                }

                @Override
                public void onDisconnected(CameraDevice camera) {
                    camera.close();
                }

                @Override
                public void onError(CameraDevice camera, int error) {
                    camera.close();
                    cameraDevice = null;
                }
            }, null);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    private void createCameraPreviewSession() {
        try {
            SurfaceTexture texture = textureView.getSurfaceTexture();
            assert texture != null;
            texture.setDefaultBufferSize(textureView.getWidth(), textureView.getHeight());
            Surface surface = new Surface(texture);
            captureRequestBuilder = cameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
            captureRequestBuilder.addTarget(surface);
            cameraDevice.createCaptureSession(Arrays.asList(surface), new CameraCaptureSession.StateCallback() {
                @Override
                public void onConfigured(@NonNull CameraCaptureSession session) {
                    if (null == cameraDevice) {
                        return; // 相机已经被关闭
                    }
                    captureSession = session;
                    captureRequestBuilder.set(CaptureRequest.CONTROL_MODE, CaptureRequest.CONTROL_MODE_AUTO);
                    try {
                        session.setRepeatingRequest(captureRequestBuilder.build(), null, null);
                    } catch (CameraAccessException e) {
                        e.printStackTrace();
                    }
                }

                @Override
                public void onConfigureFailed(@NonNull CameraCaptureSession session) {
                    Toast.makeText(MainActivity.this, "相机配置失败", Toast.LENGTH_SHORT).show();
                }
            }, null);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (null != captureSession) {
            captureSession.close();
            captureSession = null;
        }
        if (null != cameraDevice) {
            cameraDevice.close();
            cameraDevice = null;
        }
    }

    //接收服务器数据
    public void Recv() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (socket != null && socket.isConnected() && RECV_flag) {
                    try {
                        byte[] bytes = new byte[1024 * 64];
                        Log.i("我是AAAAAAAAA我收到啦 服务器指令", "************************");
                        int Len = inputStream.read(bytes);//获取数据
                        if (Len != -1) {  // 如果收到不为空的消息
                            String s = new String(bytes, 0, Len);
                            Message msg = myHandler.obtainMessage();//从消息队列拉取个消息变量
                            if (RECV_flag == true) {
                                Log.i("NowCommand", s);
                                Log.i("我是AAAAAAAAA我收到啦 服务器指令", "************************");
                                Log.i("我是AAAAAAAAA  RECV_flag", String.valueOf(RECV_flag));

                                msg.what = 2;//设置消息变量的 what 变量值 为3
                                msg.arg1 = Len;//接收的数据个数
                                msg.obj = s;//传递数据
                                myHandler.sendMessage(msg);//插入消息队列
                            }
                        } else {//连接异常断开
                            Message msg = myHandler.obtainMessage();//从消息队列拉取个消息变量
                            msg.what = 0;//设置消息变量的 what 变量值 为0
                            myHandler.sendMessage(msg);//插入消息队列
                            break;
                        }

                    } catch (Exception e) {//连接异常断开
                        e.printStackTrace();
                        Message msg = myHandler.obtainMessage();//从消息队列拉取个消息变量
                        msg.what = 0;//设置消息变量的 what 变量值 为0
                        myHandler.sendMessage(msg);//插入消息队列
                        break;

                    }
                }
            }
        }).start();


    }

    //发送服务器数据
    private void sendText(String message) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Log.i("message_1", message);
                    outputStream.write(message.getBytes(StandardCharsets.UTF_8));
                    textViewRec.setText("信息发送成功" + message);
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        }).start();
    }

    //收到页面更新 避免线程安全冲突
    class MyHandler extends Handler {  // 接收消息以及处理
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            switch (msg.what) {
                case 0:
                    Log.i("msg.what", "0 ");
                    Log.i("msg", "连接断开 ");
                    textViewRec.setText("断开链接");
                    Toast.makeText(mActivity, "断开连接", Toast.LENGTH_SHORT).show();

                    break;
                case 1:
                    Log.i("msg.what", "1 ");
                    Log.i("msg", "与服务器连接成功 ");

                    break;
                case 2:
                    Log.i("msg.what", "2 *****");
                    if (msg.obj instanceof String) {
                        String data_msg = (String) msg.obj;
                        String[] command = data_msg.split(" ");
                        Log.i("Tab", data_msg);
                        Log.i("准备设置预览框", data_msg);
                        textViewRec.setText("接收到的服务器数据:" + data_msg);
                        Log.i("接收到的服务器数据", data_msg);
                        //       ddde                   s
                        if (command[0].equals("egg")) {
                            data = command[1];
                            textViewRec.setText("接收到的服务器数据:" + data);
                            parseData();
                            updateSpinnerTimeData();  // 更新时间下拉选项框

                        }
                        if (command[0].equals("Sensor")) {
                            String temperature_humidity_lightIntensity_eggplant_quantity_data = command[1];
                            String[] sensor_data = temperature_humidity_lightIntensity_eggplant_quantity_data.split("-");

                            temperature = sensor_data[0]+"℃";
                            humidity = "85%";
                            lightIntensity = sensor_data[2]+"lx";
                            eggplant_quantity_data = sensor_data[3].replaceAll("\\s*\r\n","")+"个";
                            picking_efficiency_of_eggplant_data = sensor_data[3].replaceAll("\\s*\r\n","")+"/h";
                            //data = "1-长茄-"+eggplant_quantity_data+"-100%-A棚-24/7/17#2-紫茄-3个-100%-B棚-24/7/17#3-长茄-3个-100%-C棚-24/7/17#4-紫茄-5个-100%-B棚-24/7/17#5-长茄-4个-100%-C棚-24/7/17";
                            data = "1-长茄-"+eggplant_quantity_data+"-100%-A棚-24/7/18#2-紫茄-3个-100%-B棚-24/7/17#3-长茄-3个-100%-C棚-24/7/16#4-紫茄-5个-100%-B棚-24/7/15#5-圆茄-4个-100%-C棚-24/7/14";

                            parseData();

                            update_robot( 0);
//                            Sensor 30.2-99.8-0.35-5
//                            帧头 温度-湿度-光照强度-采摘个数
                        }
//                        if (command[0].equals("daytemplow")) {
//                            data = command[1];
//                            textViewRec.setText("接收到的服务器数据:" + data);
//                            AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
//                            builder.setTitle("警告");
//                            builder.setMessage("白天气温过低...");
//                            builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
//                                @Override
//                                public void onClick(DialogInterface dialog, int which) {
//
//                                }
//                            });
//                            builder.show();
//                        }
//                        if (command[0].equals("daytemphigh")) {
//                            data = command[1];
//                            textViewRec.setText("接收到的服务器数据:" + data);
//                            AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
//                            builder.setTitle("警告");
//                            builder.setMessage("白天气温过高...");
//                            builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
//                                @Override
//                                public void onClick(DialogInterface dialog, int which) {
//
//                                }
//                            });
//                            builder.show();
//                        }
//                        if (command[0].equals("nighttemplow")) {
//                            data = command[1];
//                            textViewRec.setText("接收到的服务器数据:" + data);
//                            AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
//                            builder.setTitle("警告");
//                            builder.setMessage("夜晚气温过低...");
//                            builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
//                                @Override
//                                public void onClick(DialogInterface dialog, int which) {
//
//                                }
//                            });
//                            builder.show();
//                        }
//                        if (command[0].equals("nighttemphigh")) {
//                            data = command[1];
//                            textViewRec.setText("接收到的服务器数据:" + data);
//                            AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
//                            builder.setTitle("警告");
//                            builder.setMessage("夜晚气温过高...");
//                            builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
//                                @Override
//                                public void onClick(DialogInterface dialog, int which) {
//
//                                }
//                            });
//                            builder.show();
//                        }


                    }
                    break;
                case 3:
                    Log.i("msg.what", "3 ");
                    Log.i("msg", "连接断开 ");
                    textViewRec.setText("与服务器连接失败，请尝试开启服务器");
                    Toast.makeText(mActivity, "连接异常", Toast.LENGTH_SHORT).show();
                    break;
                case 4:
                    textViewRec.setText("接受数据自动去重");
                    break;
            }
        }
    }

    //折线图日期
    public class DateAxisValueFormatter extends ValueFormatter {
        private final Calendar calendar = Calendar.getInstance();

        public DateAxisValueFormatter() {
            calendar.set(2024, Calendar.JULY, 8);  // 设置起始日期为2023年7月8日
        }

        @Override
        public String getFormattedValue(float value) {
            calendar.set(Calendar.DAY_OF_YEAR, 1 + (int) value);  // 从1月1日开始，增加天数
            SimpleDateFormat sdf = new SimpleDateFormat("MM/dd", Locale.getDefault());
            return sdf.format(calendar.getTime());
        }
    }

    //更新下拉选项框
    private void updateSpinnerTimeData() {
        HashSet<String> uniqueTimes = new HashSet<>(time);
        ArrayList<String> timeOptions = new ArrayList<>(uniqueTimes);

        // 使用Collections.sort()对时间进行排序，需要提供Comparator来实现降序排序
        Collections.sort(timeOptions, new Comparator<String>() {
            @Override
            public int compare(String o1, String o2) {
                // 假设日期格式为"yy/MM/dd"，这里将字符串转换为日期对象进行比较
                SimpleDateFormat sdf = new SimpleDateFormat("yy/MM/dd");
                try {
                    Date date1 = sdf.parse(o1);
                    Date date2 = sdf.parse(o2);
                    return date2.compareTo(date1); // 降序排序
                } catch (ParseException e) {
                    e.printStackTrace();
                    return 0;
                }
            }
        });

        // 将"全部"添加到列表的最前面
        timeOptions.add(0, "全部");

        // 清空原有的选项并设置新的适配器
        ArrayAdapter<String> timeAdapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, timeOptions);
        timeAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner_time.setAdapter(null); // 清空原有选项
        spinner_time.setAdapter(timeAdapter); // 重新设置适配器
    }

}