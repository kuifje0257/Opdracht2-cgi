window.addEventListener('load', (event) => {
    console.log('page is fully loaded');

    fetch('data.json')
        .then(response => 
            response.json()
        )
        .then(data => {
            var tbl = document.getElementById("tblData");
            data.forEach(data => {
                console.log(data)
                let DT = new Date();
                let hours =DT.getHours();
                let minutes = DT.getMinutes();
                let seconds = DT.getSeconds();
                let Mseconds = DT.getMilliseconds();
                console.log(Mseconds)

                if(hours <10)
                    hours = "0"+hours;
                if(minutes<10)
                    minutes = "0"+minutes;
                if(seconds<10)                    
                    seconds = "0"+seconds;

                if(Mseconds<10)                    
                    Mseconds = "000"+Mseconds;
                if(10<=Mseconds && Mseconds<100)          
                    Mseconds = "00"+Mseconds;
                if(Mseconds<1000 && Mseconds>=100)          
                    Mseconds = "0"+Mseconds;
                
                let Time = hours+':'+minutes+":"+seconds+":"+Mseconds;
                let htmlItem = `<tr><td>${data.FirstName}</dt>
                                <td>${data.LastName}</dt>
                                <td>${Time}</tr>`;
                
                                tbl.innerHTML += htmlItem;


            })
        })
        
});
