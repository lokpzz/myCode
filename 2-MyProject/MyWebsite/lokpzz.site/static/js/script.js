console.log('%cCopyright © 2024 zyyo.net',
    'background-color: #ff00ff; color: white; font-size: 24px; font-weight: bold; padding: 10px;'
);
console.log('%c   /\\_/\\', 'color: #8B4513; font-size: 20px;');
console.log('%c  ( o.o )', 'color: #8B4513; font-size: 20px;');
console.log(' %c  > ^ <', 'color: #8B4513; font-size: 20px;');
console.log('  %c /  ~ \\', 'color: #8B4513; font-size: 20px;');
console.log('  %c/______\\', 'color: #8B4513; font-size: 20px;');

document.addEventListener('contextmenu', function (event) {
    event.preventDefault();
});

function handlePress(event) {
    this.classList.add('pressed');
}

function handleRelease(event) {
    this.classList.remove('pressed');
}

function handleCancel(event) {
    this.classList.remove('pressed');
}

var buttons = document.querySelectorAll('.projectItem');
buttons.forEach(function (button) {
    button.addEventListener('mousedown', handlePress);
    button.addEventListener('mouseup', handleRelease);
    button.addEventListener('mouseleave', handleCancel);
    button.addEventListener('touchstart', handlePress);
    button.addEventListener('touchend', handleRelease);
    button.addEventListener('touchcancel', handleCancel);
});

function toggleClass(selector, className) {
    var elements = document.querySelectorAll(selector);
    elements.forEach(function (element) {
        element.classList.toggle(className);
    });
}

function pop(imageURL) {
    var tcMainElement = document.querySelector(".tc-img");
    if (imageURL) {
        tcMainElement.src = imageURL;
    }
    toggleClass(".tc-main", "active");
    toggleClass(".tc", "active");
}

var tc = document.getElementsByClassName('tc');
var tc_main = document.getElementsByClassName('tc-main');
tc[0].addEventListener('click', function (event) {
    pop();
});
tc_main[0].addEventListener('click', function (event) {
    event.stopPropagation();
});



function setCookie(name, value, days) {
    var expires = "";
    if (days) {
        var date = new Date();
        date.setTime(date.getTime() + days * 24 * 60 * 60 * 1000);
        expires = "; expires=" + date.toUTCString();
    }
    document.cookie = name + "=" + value + expires + "; path=/";
}

function getCookie(name) {
    var nameEQ = name + "=";
    var cookies = document.cookie.split(';');
    for (var i = 0; i < cookies.length; i++) {
        var cookie = cookies[i];
        while (cookie.charAt(0) == ' ') {
            cookie = cookie.substring(1, cookie.length);
        }
        if (cookie.indexOf(nameEQ) == 0) {
            return cookie.substring(nameEQ.length, cookie.length);
        }
    }
    return null;
}















document.addEventListener('DOMContentLoaded', function () {






    var html = document.querySelector('html');
    var themeState = getCookie("themeState") || "Light";
    var tanChiShe = document.getElementById("tanChiShe");






    function changeTheme(theme) {
        tanChiShe.src = "./static/svg/snake-" + theme + ".svg";
        html.dataset.theme = theme;
        setCookie("themeState", theme, 365);
        themeState = theme;
    }







    var Checkbox = document.getElementById('myonoffswitch')
    Checkbox.addEventListener('change', function () {
        if (themeState == "Dark") {
            changeTheme("Light");
        } else if (themeState == "Light") {
            changeTheme("Dark");
        } else {
            changeTheme("Dark");
        }
    });



    if (themeState == "Dark") {
        Checkbox.checked = false;
    }

    changeTheme(themeState);

















   

    var fpsElement = document.createElement('div');
    fpsElement.id = 'fps';
    fpsElement.style.zIndex = '10000';
    fpsElement.style.position = 'fixed';
    fpsElement.style.left = '0';
    document.body.insertBefore(fpsElement, document.body.firstChild);

    var showFPS = (function () {
        var requestAnimationFrame = window.requestAnimationFrame ||
            window.webkitRequestAnimationFrame ||
            window.mozRequestAnimationFrame ||
            window.oRequestAnimationFrame ||
            window.msRequestAnimationFrame ||
            function (callback) {
                window.setTimeout(callback, 1000 / 60);
            };

        var fps = 0,
            last = Date.now(),
            offset, step, appendFps;

        step = function () {
            offset = Date.now() - last;
            fps += 1;

            if (offset >= 1000) {
                last += offset;
                appendFps(fps);
                fps = 0;
            }

            requestAnimationFrame(step);
        };

        appendFps = function (fpsValue) {
            fpsElement.textContent = 'FPS: ' + fpsValue;
        };

        step();
    })();
    
    // 从后台加载配置数据并更新前台
    function loadAdminConfig() {
        try {
            const adminData = localStorage.getItem('zyyoAdminData');
            if (!adminData) {
                console.log('未找到后台配置数据，使用默认数据');
                return;
            }
            
            const config = JSON.parse(adminData);
            console.log('加载后台配置:', config);
            
            // 更新项目列表
            if (config.projects && config.projects.length > 0) {
                updateProjectList(config.projects);
            }
            
            // 更新标签
            if (config.tags && config.tags.length > 0) {
                updateTags(config.tags);
            }
            
            // 更新时间线
            if (config.timeline && config.timeline.length > 0) {
                updateTimeline(config.timeline);
            }
            
            // 更新个人信息
            if (config.info) {
                updateInfo(config.info);
            }
            
            // 应用设置
            if (config.settings) {
                applySettings(config.settings);
            }
            
            // 应用 GitHub 图表
            if (config.github && config.github.enabled) {
                applyGithubChart(config.github);
            }
            
            console.log('前台数据已更新');
        } catch (e) {
            console.error('加载后台配置失败:', e);
        }
    }
    
    // 更新项目列表
    function updateProjectList(projects) {
        const projectLists = document.querySelectorAll('.projectList');
        if (projectLists.length === 0) return;
        
        // 按分类分组项目
        const siteProjects = projects.filter(p => p.category === 'site');
        const projectProjects = projects.filter(p => p.category === 'project');
        
        // 更新 site 类别的项目
        if (siteProjects.length > 0 && projectLists[0]) {
            projectLists[0].innerHTML = siteProjects.map(project => `
                <a class="projectItem a" target="_blank" href="${project.url}">
                    <div class="projectItemLeft">
                        <h1>${project.title}</h1>
                        <p>${project.desc}</p>
                    </div>
                    <div class="projectItemRight">
                        <img src="${project.icon}" alt="">
                    </div>
                </a>
            `).join('');
        }
        
        // 更新 project 类别的项目
        if (projectProjects.length > 0 && projectLists[1]) {
            projectLists[1].innerHTML = projectProjects.map(project => `
                <a class="projectItem b" target="_blank" href="${project.url}">
                    <div class="projectItemLeft">
                        <h1>${project.title}</h1>
                        <p>${project.desc}</p>
                    </div>
                    <div class="projectItemRight">
                        <img src="${project.icon}" alt="">
                    </div>
                </a>
            `).join('');
        }
    }
    
    // 更新标签
    function updateTags(tags) {
        const tagContainer = document.querySelector('.left-tag');
        if (!tagContainer || tags.length === 0) return;
        
        tagContainer.innerHTML = tags.map(tag => `
            <div class="left-tag-item">${tag}</div>
        `).join('');
    }
    
    // 更新时间线
    function updateTimeline(timeline) {
        const timelineContainer = document.querySelector('#line');
        if (!timelineContainer || timeline.length === 0) return;
        
        timelineContainer.innerHTML = timeline.map(item => `
            <li>
                <div class="focus"></div>
                <div>${item.event}</div>
                <div>${item.date}</div>
            </li>
        `).join('');
    }
    
    // 更新个人信息
    function updateInfo(info) {
        // 更新位置信息
        const locationElement = document.querySelector('.left-des-item');
        if (locationElement && info.location) {
            const svgIcon = locationElement.querySelector('svg');
            locationElement.innerHTML = '';
            if (svgIcon) locationElement.appendChild(svgIcon);
            locationElement.appendChild(document.createTextNode(info.location));
        }
        
        // 更新组织信息
        const orgElement = document.querySelectorAll('.left-des-item')[1];
        if (orgElement && info.organization) {
            const svgIcon = orgElement.querySelector('svg');
            orgElement.innerHTML = '';
            if (svgIcon) orgElement.appendChild(svgIcon);
            orgElement.appendChild(document.createTextNode(info.organization));
        }
        
        // 更新描述
        const descElement = document.querySelector('.description');
        if (descElement && info.description) {
            const parts = descElement.innerHTML.split('  ');
            if (parts.length > 1) {
                descElement.innerHTML = parts[0] + '  ' + info.description;
            }
        }
        
        // 更新欢迎语中的名字
        const nameElement = document.querySelector('.gradientText');
        if (nameElement && info.nickname) {
            nameElement.textContent = info.nickname;
        }
    }
    
    // 应用设置
    function applySettings(settings) {
        // 隐藏/显示侧边栏
        const sidebar = document.querySelector('.zyyo-left');
        if (sidebar) {
            sidebar.style.display = settings.showSidebar !== false ? 'block' : 'none';
        }
    }
    
    // 应用 GitHub 图表
    function applyGithubChart(github) {
        if (!github.enabled || !github.username) return;
        
        // 创建或获取 GitHub 图表容器
        let githubContainer = document.getElementById('githubChart');
        
        if (!githubContainer) {
            // 在 skill 容器下方创建新容器
            const skillContainer = document.querySelector('.skill');
            if (!skillContainer) return;
            
            githubContainer = document.createElement('div');
            githubContainer.id = 'githubChart';
            githubContainer.style.cssText = 'margin-top: 20px; padding: 20px; background: rgba(255,255,255,0.95); border-radius: 12px; box-shadow: 0 8px 32px rgba(0,0,0,0.1); text-align: center;';
            skillContainer.parentNode.insertBefore(githubContainer, skillContainer.nextSibling);
        }
        
        // 构建图表 URL
        const chartUrl = github.customUrl || `https://ghchart.rshah.org/000000/${github.username}`;
        
        // 加载图表
        githubContainer.innerHTML = `
            <img src="${chartUrl}" alt="GitHub Contributions" style="max-width: 100%; height: auto;">
        `;
        
        console.log('GitHub 图表已加载:', github.username);
    }
    
    // 页面加载完成后执行
    window.addEventListener('load', function() {
        // 延迟一点执行，确保 DOM 已加载
        setTimeout(loadAdminConfig, 500);
    });
    
    // pop('./static/img/tz.jpg')
    
    
    
});




var pageLoading = document.querySelector("#zyyo-loading");
window.addEventListener('load', function() {
    setTimeout(function () {
        pageLoading.style.opacity = '0';
    }, 100);
});

