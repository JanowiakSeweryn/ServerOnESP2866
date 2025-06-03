const ServoOn = class{
    constructor(ip_on,ip_off,id1,id2){

        this.ip_on = ip_on;
        this.ip_off = ip_off;
        this.id1 = id1;
        this.id2 = id2;

        this.counter = 0;
        this.interval = null;

        this.hold = this.hold.bind(this);
        this.StartHold = this.StartHold.bind(this);
        this.StopHold  = this.StopHold.bind(this);
    }
    
    hold(){
        this.counter++;
        document.getElementById(this.id2).textContent = this.counter;
    }
    StartHold(){
        console.log(this.counter);
        fetch(this.ip_on)
        // .then(respone=>respone.json());
        this.interval = setInterval(this.hold,100);
    }
    StopHold(){
        this.counter = 0;
        fetch(this.ip_off)
        // .then(respone=>respone.json());
        clearInterval(this.interval);
    }

    HoldingButton(){

        const butt = document.getElementById(this.id1);

    //for PC/laptop 
        butt.addEventListener('mousedown', (e) => {
            e.preventDefault();
            this.StartHold();},{passive:false});

        butt.addEventListener('pointerup', (e) => {
            e.preventDefault();
            this.StopHold();},{passive:false});

        butt.addEventListener('pointeroff', (e) => {
            e.preventDefault();
            this.StopHold();},{passive:false});
        

    //for mobile device:---------------
        butt.addEventListener('touchstart', (e) => {
            e.preventDefault();
            this.StartHold();},{passive:false});

        butt.addEventListener('touchend', (e) => {
            e.preventDefault();
            this.StopHold();},{passive:false});

        butt.addEventListener('touchcancel', this.StopHold);
    }

}

//LED_GREEN -> servo turn direction 0
const led_g_on = "http://192.168.10.1/led_g_on";
const led_g_off = "http://192.168.10.1/led_g_off";
const Led_green = new ServoOn(led_g_on,led_g_off,"g_id","g_t");

//LED_RED -> servo turn direction 1 
const led_r_on = "http://192.168.10.1/led_r_on";
const led_r_off = "http://192.168.10.1/led_r_off";
const Led_red = new ServoOn(led_r_on,led_r_off,'r_id',"r_t");

Led_red.HoldingButton();
Led_green.HoldingButton(); 

//slider:

const slider1 = document.getElementById('mySlider1');
const output1 = document.getElementById('sliderValue1');

slider1.addEventListener('input', () => {
    output1.textContent = slider1.value;
});

const slider2 = document.getElementById('mySlider2');
const output2 = document.getElementById('sliderValue2');

slider2.addEventListener('input', () => {
    output2.textContent = slider2.value;
});