
(function(){
    
    // Inicia o firebase Firebase
    const config = {
      apiKey: "AIzaSyDL1wdZ5GTQAKoIKTPJCvgpUXQUir5anvM",
      authDomain: "projeto-estufa-inteligente.firebaseapp.com",
      databaseURL: "https://projeto-estufa-inteligente.firebaseio.com",
      projectId: "projeto-estufa-inteligente",
      storageBucket: "projeto-estufa-inteligente.appspot.com",
      messagingSenderId: "95724281701",
      appId: "1:95724281701:web:8d4eef74b31d7001ef0b8c"
    };
    firebase.initializeApp(config);

    var db = firebase.database();

    // Cria os listeners dos dados no firebase
    var tempRef = db.ref('temperatura');
    var umidArRef = db.ref('humidadeAr');
    var umidSoloRef = db.ref('humidadeSolo');
    var ativaCooler = db.ref('ativaCooler');
    var ativaLampada = db.ref('ativaLampada');
    var ativaValvula = db.ref('ativaValvula');

    // Registra as funções que atualizam os gráficos e dados atuais da telemetria
    tempRef.on('value', onNewData('currentTemp', 'tempLineChart' , 'Temperatura', 'C°'));
    umidArRef.on('value', onNewData('currentUmidAr', 'umidArLineChart' , 'Umidade do Ar', '%'));
    umidSoloRef.on('value', onNewData('currentUmidSolo', 'umidSoloLineChart' , 'Umidade do Solo', '%'));

    ativaCooler.on('value', function(snapshot){
        var value3 = snapshot.val();
        var el = document.getElementById('ativaCooler')
        if(value3){
            el.classList.add('green-text');
            document.getElementById('coolerAtv').innerText = 'Ativado';
        }else{
            el.classList.remove('green-text');
            document.getElementById('coolerAtv').innerText = 'Desativado';
        }
    });

    ativaLampada.on('value', function(snapshot){
        var value2 = snapshot.val();
        var el = document.getElementById('ativaLamp')
        if(value2){
            el.classList.add('amber-text');
            document.getElementById('lampAtivada').innerText = 'Ativado';
        }else{
            el.classList.remove('amber-text');
            document.getElementById('lampAtivada').innerText = 'Desativado';
        }
    });

    ativaValvula.on('value', function(snapshot){
        var value1 = snapshot.val();
        var el = document.getElementById('ativaValvula')
        if(value1){
            el.classList.add('cyan-text');
            document.getElementById('valvAtivada').innerText = 'Ativado';
        }else{
            el.classList.remove('cyan-text');
            document.getElementById('valvAtivada').innerText = 'Desativado';
        }
    });

})();


// Retorna uma função que de acordo com as mudanças dos dados
// Atualiza o valor atual do elemento, com a metrica passada (currentValueEl e metric)
// e monta o gráfico com os dados e descrição do tipo de dados (chartEl, label)
function onNewData(currentValueEl, chartEl, label, metric){
    return function(snapshot){
        var readings = snapshot.val();
        if(readings){
            var currentValue;
            var data = [];
            for(var key in readings){
                currentValue = readings[key]
                data.push(currentValue);
                if(data.length > 144){
                    data.shift();
                }
            }
            console.log(data.length);
            document.getElementById(currentValueEl).innerText = currentValue + ' ' + metric;
            buildLineChart(chartEl, label, data);
        }
    }
}('value', function(snapshot){   
});

// Constroi um gráfico de linha no elemento (el) com a descrição (label) e os
// dados passados (data)
function buildLineChart(el, label, data){
  var elNode = document.getElementById(el);
  new Chart(elNode, {
    type: 'line',
    data: {
        labels: new Array(data.length).fill(""),
        datasets: [{
            label: label,
            data: data,
            borderWidth: 1,
            fill: false,
            spanGaps: false,
            lineTension: 0.1,
            backgroundColor: "#F9A825",
            borderColor: "#F9A825"
        }]
    }
  });
}
