// 后台管理主逻辑

// 数据模型
let data = {
    projects: [
        { id: 1, title: '博客', desc: '记录摆烂日常', url: 'https://blog.zyyo.net', icon: './static/img/i1.png', category: 'site' },
        { id: 2, title: '云盘', desc: '存储收集文件', url: 'https://i.zyyo.cc', icon: './static/img/i2.png', category: 'site' },
        { id: 3, title: '实验室', desc: '收集有趣 html 作品', url: 'https://zyyo.cc', icon: './static/img/i4.png', category: 'project' },
        { id: 4, title: '实验室', desc: '收集有趣 html 作品', url: 'https://zyyo.cc', icon: './static/img/i4.png', category: 'project' }
    ],
    tags: ['网瘾', '小学生', '大一', '网页', 'linux', '跑者', '前端', '骑行'],
    timeline: [
        { id: 1, event: '敬请期待', date: '2024.1' },
        { id: 2, event: 'ICP 备案成功', date: '2023.8' },
        { id: 3, event: '注册域名 zyyo.net', date: '2023.3' },
        { id: 4, event: '出来后洗心革面', date: '2021.2' },
        { id: 5, event: '...', date: '...' },
        { id: 6, event: '搭建第一个网站', date: '2018.1' }
    ],
    info: {
        nickname: 'lokpzz',
        description: '嬉游醉眼，莫负青春',
        location: 'China-Henan',
        organization: 'Sias',
        avatar: './static/img/logo.png',  // 头像
        avatarFrame: './static/img/logokuang.png',  // 头像框
        background: './static/img/background.jpg',  // 背景图
        jobTitle: 'Full Stack',  // 职业描述
        jobEmoji: '👦'  // 职业表情
    },
    github: {
        enabled: false,
        username: '',  // GitHub 用户名
        customUrl: ''  // 自定义图表链接
    },
    socialLinks: [
        { id: 1, name: 'GitHub', url: 'https://github.com/ZYYO666', icon: 'github', enabled: true },
        { id: 2, name: 'Email', url: 'mailto:i@zyyo.net', icon: 'email', enabled: true },
        { id: 3, name: '赞助', url: '', icon: 'donate', image: './static/img/wxzsm.jpg', enabled: true },
        { id: 4, name: 'QQ', url: '', icon: 'qq', image: './static/img/qq.jpg', enabled: true }
    ],
    settings: {
        showSidebar: true
    }
};

// 初始化
document.addEventListener('DOMContentLoaded', function() {
    console.log('后台管理系统已加载');
    checkAuth();
    loadFromStorage();
    initNavigation();
    renderAll();
    setupForms();
});

// 权限检查 - 已取消登录验证
function checkAuth() {
    // 无需登录验证，直接进入后台
}

// 从本地存储加载数据
function loadFromStorage() {
    const savedData = localStorage.getItem('zyyoAdminData');
    if (savedData) {
        try {
            const parsed = JSON.parse(savedData);
            data = { ...data, ...parsed };
        } catch (e) {
            console.error('加载数据失败:', e);
        }
    }
}

// 保存到本地存储
function saveToStorage() {
    localStorage.setItem('zyyoAdminData', JSON.stringify(data));
}

// 导航初始化
function initNavigation() {
    const navItems = document.querySelectorAll('.nav-item');
    navItems.forEach(item => {
        item.addEventListener('click', function(e) {
            e.preventDefault();
            const page = this.dataset.page;
            showPage(page);
        });
    });

    // 退出登录按钮已移除
}

// 显示页面
function showPage(pageName) {
    // 更新导航状态
    document.querySelectorAll('.nav-item').forEach(item => {
        item.classList.remove('active');
        if (item.dataset.page === pageName) {
            item.classList.add('active');
        }
    });

    // 更新页面标题
    const titles = {
        dashboard: '控制台',
        projects: '项目管理',
        tags: '标签管理',
        timeline: '时间线管理',
        info: '个人信息',
        social: '社交链接',
        settings: '设置'
    };
    document.getElementById('pageTitle').textContent = titles[pageName] || '控制台';

    // 切换页面内容
    document.querySelectorAll('.page').forEach(page => {
        page.classList.remove('active');
    });
    document.getElementById(pageName + 'Page').classList.add('active');

    // 渲染对应页面
    renderPage(pageName);
}

// 渲染页面
function renderPage(pageName) {
    switch(pageName) {
        case 'dashboard':
            updateStats();
            break;
        case 'projects':
            renderProjects();
            break;
        case 'tags':
            renderTags();
            break;
        case 'timeline':
            renderTimeline();
            break;
        case 'info':
            loadInfoForm();
            break;
        case 'github':
            loadGithubSettings();
            break;
        case 'social':
            renderSocialLinks();
            break;
        case 'settings':
            loadSettings();
            break;
    }
}

// 渲染所有
function renderAll() {
    updateStats();
    renderProjects();
    renderTags();
    renderTimeline();
    renderSocialLinks();
    loadInfoForm();
    loadSettings();
    loadGithubSettings();
}

// 更新统计
function updateStats() {
    document.getElementById('projectCount').textContent = data.projects.length;
    document.getElementById('tagCount').textContent = data.tags.length;
    document.getElementById('timelineCount').textContent = data.timeline.length;
}

// 渲染项目列表
function renderProjects() {
    const container = document.getElementById('projectsList');
    container.innerHTML = '';
    
    data.projects.forEach(project => {
        const item = document.createElement('div');
        item.className = 'list-item';
        item.innerHTML = `
            <div class="item-info">
                <div class="item-title">${escapeHtml(project.title)} (${project.category})</div>
                <div class="item-desc">${escapeHtml(project.desc)}</div>
                <div class="item-desc" style="font-size: 12px; color: #999;">${escapeHtml(project.url)}</div>
            </div>
            <div class="item-actions">
                <button class="btn-edit" onclick="editProject(${project.id})">✏️ 编辑</button>
                <button class="btn-delete" onclick="deleteProject(${project.id})">🗑️ 删除</button>
            </div>
        `;
        container.appendChild(item);
    });
}

// 渲染标签列表
function renderTags() {
    const container = document.getElementById('tagsList');
    container.innerHTML = '';
    
    data.tags.forEach((tag, index) => {
        const item = document.createElement('div');
        item.className = 'tag-item';
        item.innerHTML = `
            <span>${escapeHtml(tag)}</span>
            <button class="tag-delete" onclick="deleteTag(${index})">×</button>
        `;
        container.appendChild(item);
    });
}

// 渲染时间线
function renderTimeline() {
    const container = document.getElementById('timelineList');
    container.innerHTML = '';
    
    data.timeline.forEach(item => {
        const timelineItem = document.createElement('div');
        timelineItem.className = 'timeline-item';
        timelineItem.innerHTML = `
            <div class="timeline-content">
                <div class="timeline-event">${escapeHtml(item.event)}</div>
                <div class="timeline-date">${escapeHtml(item.date)}</div>
            </div>
            <div class="timeline-actions">
                <button class="btn-edit" onclick="editTimeline(${item.id})">✏️ 编辑</button>
                <button class="btn-delete" onclick="deleteTimeline(${item.id})">🗑️ 删除</button>
            </div>
        `;
        container.appendChild(timelineItem);
    });
}

// 加载信息表单
function loadInfoForm() {
    if (!data.info) return;
    document.getElementById('nickname').value = data.info.nickname || '';
    document.getElementById('description').value = data.info.description || '';
    document.getElementById('location').value = data.info.location || '';
    document.getElementById('organization').value = data.info.organization || '';
    document.getElementById('avatar').value = data.info.avatar || '';
    document.getElementById('avatarFrame').value = data.info.avatarFrame || '';
    document.getElementById('background').value = data.info.background || '';
    document.getElementById('jobTitle').value = data.info.jobTitle || '';
    document.getElementById('jobEmoji').value = data.info.jobEmoji || '';
}

// 加载设置
function loadSettings() {
    document.getElementById('showSidebar').checked = data.settings.showSidebar;
}

// 设置表单
function setupForms() {
    // 项目表单
    document.getElementById('projectForm').addEventListener('submit', function(e) {
        e.preventDefault();
        saveProject();
    });

    // 标签表单
    document.getElementById('tagForm').addEventListener('submit', function(e) {
        e.preventDefault();
        saveTag();
    });

    // 时间线表单
    document.getElementById('timelineForm').addEventListener('submit', function(e) {
        e.preventDefault();
        saveTimeline();
    });

    // 信息表单
    document.getElementById('infoForm').addEventListener('submit', function(e) {
        e.preventDefault();
        saveInfo();
    });

    // 社交链接表单
    document.getElementById('socialForm').addEventListener('submit', function(e) {
        e.preventDefault();
        saveSocialLink(e);
    });
}

// 项目操作
function openProjectModal(editId = null) {
    const modal = document.getElementById('projectModal');
    const form = document.getElementById('projectForm');
    form.reset();
    
    if (editId) {
        const project = data.projects.find(p => p.id === editId);
        if (project) {
            document.getElementById('projectId').value = project.id;
            document.getElementById('projectTitle').value = project.title;
            document.getElementById('projectDesc').value = project.desc;
            document.getElementById('projectUrl').value = project.url;
            document.getElementById('projectIcon').value = project.icon;
            document.getElementById('projectCategory').value = project.category;
            document.getElementById('projectModalTitle').textContent = '编辑项目';
        }
    } else {
        document.getElementById('projectId').value = '';
        document.getElementById('projectModalTitle').textContent = '添加项目';
    }
    
    modal.classList.add('active');
}

function closeProjectModal() {
    document.getElementById('projectModal').classList.remove('active');
}

function saveProject() {
    const id = document.getElementById('projectId').value;
    const project = {
        id: id ? parseInt(id) : Date.now(),
        title: document.getElementById('projectTitle').value,
        desc: document.getElementById('projectDesc').value,
        url: document.getElementById('projectUrl').value,
        icon: document.getElementById('projectIcon').value,
        category: document.getElementById('projectCategory').value
    };
    
    if (id) {
        const index = data.projects.findIndex(p => p.id == id);
        data.projects[index] = project;
    } else {
        data.projects.push(project);
    }
    
    saveToStorage();
    closeProjectModal();
    renderProjects();
    updateStats();
    alert('保存成功！');
}

function editProject(id) {
    openProjectModal(id);
}

function deleteProject(id) {
    if (confirm('确定要删除这个项目吗？')) {
        data.projects = data.projects.filter(p => p.id !== id);
        saveToStorage();
        renderProjects();
        updateStats();
    }
}

// 标签操作
function openTagModal() {
    document.getElementById('tagForm').reset();
    document.getElementById('tagId').value = '';
    document.getElementById('tagModalTitle').textContent = '添加标签';
    document.getElementById('tagModal').classList.add('active');
}

function closeTagModal() {
    document.getElementById('tagModal').classList.remove('active');
}

function saveTag() {
    const tagName = document.getElementById('tagName').value.trim();
    if (tagName) {
        data.tags.push(tagName);
        saveToStorage();
        closeTagModal();
        renderTags();
        updateStats();
        alert('添加成功！');
    }
}

function deleteTag(index) {
    if (confirm('确定要删除这个标签吗？')) {
        data.tags.splice(index, 1);
        saveToStorage();
        renderTags();
        updateStats();
    }
}

// 时间线操作
function openTimelineModal(editId = null) {
    const modal = document.getElementById('timelineModal');
    const form = document.getElementById('timelineForm');
    form.reset();
    
    if (editId) {
        const item = data.timeline.find(t => t.id === editId);
        if (item) {
            document.getElementById('timelineId').value = item.id;
            document.getElementById('timelineEvent').value = item.event;
            document.getElementById('timelineDate').value = item.date;
            document.getElementById('timelineModalTitle').textContent = '编辑时间线';
        }
    } else {
        document.getElementById('timelineId').value = '';
        document.getElementById('timelineModalTitle').textContent = '添加时间线';
    }
    
    modal.classList.add('active');
}

function closeTimelineModal() {
    document.getElementById('timelineModal').classList.remove('active');
}

function saveTimeline() {
    const id = document.getElementById('timelineId').value;
    const item = {
        id: id ? parseInt(id) : Date.now(),
        event: document.getElementById('timelineEvent').value,
        date: document.getElementById('timelineDate').value
    };
    
    if (id) {
        const index = data.timeline.findIndex(t => t.id == id);
        data.timeline[index] = item;
    } else {
        data.timeline.push(item);
    }
    
    saveToStorage();
    closeTimelineModal();
    renderTimeline();
    updateStats();
    alert('保存成功！');
}

function editTimeline(id) {
    openTimelineModal(id);
}

function deleteTimeline(id) {
    if (confirm('确定要删除这个时间线吗？')) {
        data.timeline = data.timeline.filter(t => t.id !== id);
        saveToStorage();
        renderTimeline();
        updateStats();
    }
}

// 保存信息
function saveInfo() {
    data.info = {
        nickname: document.getElementById('nickname').value,
        description: document.getElementById('description').value,
        location: document.getElementById('location').value,
        organization: document.getElementById('organization').value,
        avatar: document.getElementById('avatar').value,
        avatarFrame: document.getElementById('avatarFrame').value,
        background: document.getElementById('background').value,
        jobTitle: document.getElementById('jobTitle').value,
        jobEmoji: document.getElementById('jobEmoji').value
    };
    
    saveToStorage();
    alert('信息保存成功！');
}

// 保存设置
function saveSettings() {
    data.settings = {
        showSidebar: document.getElementById('showSidebar').checked
    };
    
    saveToStorage();
    alert('设置保存成功！');
}

// 社交链接管理
function renderSocialLinks() {
    const container = document.getElementById('socialList');
    if (!container) return;
    
    if (!data.socialLinks || data.socialLinks.length === 0) {
        container.innerHTML = '<p style="color: #999; text-align: center; padding: 40px;">暂无社交链接</p>';
        return;
    }
    
    let html = '';
    data.socialLinks.forEach(link => {
        html += `
            <div class="data-item" style="display: flex; justify-content: space-between; align-items: center; padding: 15px; background: white; border-radius: 8px; margin-bottom: 10px; box-shadow: 0 2px 8px rgba(0,0,0,0.1);">
                <div style="flex: 1;">
                    <div style="font-weight: 600; color: #333; margin-bottom: 5px;">${link.name}</div>
                    <div style="font-size: 13px; color: #666;">${link.url || '无链接'}</div>
                    <div style="font-size: 12px; color: #999; margin-top: 3px;">图标：${link.icon} | ${link.enabled ? '✅ 启用' : '❌ 禁用'}</div>
                </div>
                <div>
                    <button onclick="editSocialLink(${link.id})" class="action-btn" style="padding: 8px 15px; margin-right: 8px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; border: none; border-radius: 6px; cursor: pointer;">✏️ 编辑</button>
                    <button onclick="deleteSocialLink(${link.id})" class="action-btn" style="padding: 8px 15px; background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%); color: white; border: none; border-radius: 6px; cursor: pointer;">🗑️ 删除</button>
                </div>
            </div>
        `;
    });
    container.innerHTML = html;
}

function openSocialModal(id = null) {
    const modal = document.getElementById('socialModal');
    const form = document.getElementById('socialForm');
    form.reset();
    
    if (id) {
        document.getElementById('socialModalTitle').textContent = '编辑社交链接';
        const link = data.socialLinks.find(l => l.id === id);
        if (link) {
            document.getElementById('socialId').value = link.id;
            document.getElementById('socialName').value = link.name;
            document.getElementById('socialUrl').value = link.url || '';
            document.getElementById('socialIcon').value = link.icon;
            document.getElementById('socialImage').value = link.image || '';
            document.getElementById('socialEnabled').checked = link.enabled;
        }
    } else {
        document.getElementById('socialModalTitle').textContent = '添加社交链接';
        document.getElementById('socialId').value = '';
    }
    
    modal.style.display = 'block';
}

function closeSocialModal() {
    document.getElementById('socialModal').style.display = 'none';
}

function saveSocialLink(event) {
    event.preventDefault();
    
    const id = document.getElementById('socialId').value;
    const socialLink = {
        id: id ? parseInt(id) : Date.now(),
        name: document.getElementById('socialName').value,
        url: document.getElementById('socialUrl').value,
        icon: document.getElementById('socialIcon').value,
        image: document.getElementById('socialImage').value,
        enabled: document.getElementById('socialEnabled').checked
    };
    
    if (id) {
        const index = data.socialLinks.findIndex(l => l.id == id);
        if (index !== -1) {
            data.socialLinks[index] = socialLink;
        }
    } else {
        data.socialLinks.push(socialLink);
    }
    
    saveToStorage();
    closeSocialModal();
    renderSocialLinks();
    alert('保存成功！');
}

function editSocialLink(id) {
    openSocialModal(id);
}

function deleteSocialLink(id) {
    if (confirm('确定要删除这个社交链接吗？')) {
        data.socialLinks = data.socialLinks.filter(l => l.id !== id);
        saveToStorage();
        renderSocialLinks();
    }
}

// GitHub 图表设置
function loadGithubSettings() {
    if (!data.github) return;
    document.getElementById('githubEnabled').checked = data.github.enabled;
    document.getElementById('githubUsername').value = data.github.username || '';
    document.getElementById('githubCustomUrl').value = data.github.customUrl || '';
}

function saveGithubSettings() {
    data.github = {
        enabled: document.getElementById('githubEnabled').checked,
        username: document.getElementById('githubUsername').value,
        customUrl: document.getElementById('githubCustomUrl').value
    };
    
    saveToStorage();
    alert('GitHub 设置保存成功！');
}

// HTML 转义防止 XSS
function escapeHtml(text) {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
}
